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
typedef  int UInt32 ;

/* Variables and functions */
 int LZMA_RESULT_OK ; 
 scalar_t__ data ; 
 scalar_t__ offset ; 

__attribute__((used)) static int read_byte(void *object, unsigned char **buffer, UInt32 *bufferSize)
{
	static unsigned int val;

	if (((unsigned int)offset % 4) == 0) {
		val = *(unsigned int *)data;
		data += 4;
	}
	
	*bufferSize = 1;
	*buffer = ((unsigned char *)&val) + (offset++ & 3);
	
	return LZMA_RESULT_OK;
}