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

/* Variables and functions */
 scalar_t__* fdFile ; 
 size_t fdOffset ; 

int readInt( void ) {
	int i = ((unsigned int)fdFile[fdOffset] | ((unsigned int)fdFile[fdOffset+1]<<8) | ((unsigned int)fdFile[fdOffset+2]<<16) | ((unsigned int)fdFile[fdOffset+3]<<24));
	fdOffset += 4;
	return i;
}