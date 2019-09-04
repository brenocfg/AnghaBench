#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  unsigned short byte ;

/* Variables and functions */
 unsigned short* crctable ; 

void CRC_ProcessByte( unsigned short *crcvalue, byte data ){
	*crcvalue = ( *crcvalue << 8 ) ^ crctable[( *crcvalue >> 8 ) ^ data];
}