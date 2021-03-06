/*
 * Created on Thu Jan 26 2017 
 *
 * Copyright (c) 2017 Thomas Northall-Little
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#ifndef DEFINES
#include "defines.h"
#endif

#include <fcntl.h> 
#include <termios.h>	
#include <sys/ioctl.h>
#include <cerrno>
#include <string>		

#define SERIAL_PORT_0                           "/dev/ttyAMA0"
//#define SERIAL_1                                "/dev/serial0"
#define SERIAL_BAUD                             B115200 //B57600
#define SERIAL_WAIT                             1000 //in milliseconds, how long a default delay is 
#define SERIAL_DATA_BITS                        CS8  
#define SERIAL_MIN_TIME                         1
#define SERIAL_MIN_LENGTH                       1    
#define SERIAL_PARITY                           0 ///IGNPAR
#define	SERIAL_WRITE_READ_LENGTH                5
#define SERIAL_MAX_BYTES                        128
#define SERIAL_LOOP_BREAK                       50 //How many times to wait for data to be received

//object of this is so that multiple devices dont write to the Serial Port at the same time and
// that all devices use the same interface and do not interfere with each other

class SPI_Handler {
    public:
        SPI_Handler();
        ~SPI_Handler();
        void closefd();
        void openfd();
        void serialRead(uint8_t *data, int size);
        void serialWrite(uint8_t *data, int size);
    private:
        void serialFlush();
        int serial_file_descriptor; //used to address and initialise the serial port
        string serial_port;
        struct termios options; // struct for spi 
        bool isOpen; //whether the serial port has been opened already and that the address is valid
};