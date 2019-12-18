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

__attribute__((used)) static int ddr4_cs_size(unsigned i)
{
	int cs_size = 0;

	if (i == 0)
		cs_size = -1;
	else if (i == 1)
		cs_size = 1024;
	else
		/* Min cs_size = 1G */
		cs_size = 1024 * (1 << (i >> 1));

	return cs_size;
}