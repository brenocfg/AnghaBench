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
 int bus_data_generation ; 

int
bus_data_generation_check(int generation)
{
	if (generation != bus_data_generation)
		return (1);

	/* XXX generate optimised lists here? */
	return (0);
}