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

unsigned int swab32(unsigned int data)
{
	unsigned int res = 0;

	res = (data & 0x000000ff) << 24 |
				(data & 0x0000ff00) << 8  |
				(data & 0x00ff0000) >> 8  |
				(data & 0xff000000) >> 24;

	return res;
}