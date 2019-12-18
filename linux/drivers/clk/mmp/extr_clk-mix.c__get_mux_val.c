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
struct mmp_clk_mix {unsigned int* mux_table; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int _get_mux_val(struct mmp_clk_mix *mix, unsigned int mux)
{
	if (mix->mux_table)
		return mix->mux_table[mux];

	return mux;
}