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
typedef  int uint8_t ;

/* Variables and functions */

uint8_t
winChksum(uint8_t *name)
{
	int i;
	uint8_t s;

	for (s = 0, i = 11; --i >= 0; s += *name++)
		s = (s << 7) | (s >> 1);
	return s;
}