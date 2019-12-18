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
 int testcalls ; 

void
gendata(char *original_buf, char *good_buf, unsigned offset, unsigned size)
{
	while (size--) {
		good_buf[offset] = testcalls % 256; 
		if (offset % 2)
			good_buf[offset] += original_buf[offset];
		offset++;
	}
}