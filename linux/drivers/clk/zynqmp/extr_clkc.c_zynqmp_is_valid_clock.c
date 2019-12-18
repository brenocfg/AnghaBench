#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_2__ {int valid; } ;

/* Variables and functions */
 int ENODEV ; 
 TYPE_1__* clock ; 
 size_t clock_max_idx ; 

__attribute__((used)) static inline int zynqmp_is_valid_clock(u32 clk_id)
{
	if (clk_id >= clock_max_idx)
		return -ENODEV;

	return clock[clk_id].valid;
}