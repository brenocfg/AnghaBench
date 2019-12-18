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
struct vid_pll_div {unsigned int shift_val; unsigned int shift_sel; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct vid_pll_div const*) ; 
 struct vid_pll_div const* vid_pll_div_table ; 

__attribute__((used)) static const struct vid_pll_div *_get_table_val(unsigned int shift_val,
						unsigned int shift_sel)
{
	int i;

	for (i = 0 ; i < ARRAY_SIZE(vid_pll_div_table) ; ++i) {
		if (vid_pll_div_table[i].shift_val == shift_val &&
		    vid_pll_div_table[i].shift_sel == shift_sel)
			return &vid_pll_div_table[i];
	}

	return NULL;
}