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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */

int memcmp(const void *x, const void *y, size_t n)
{
	const uint8_t* x8 = (const uint8_t*)x;
	const uint8_t* y8 = (const uint8_t*)y;
	size_t i;
	for(i=0; i<n; i++) {
		if(x8[i] < y8[i])
			return -1;
		else if(x8[i] > y8[i])
			return 1;
	}
	return 0;
}