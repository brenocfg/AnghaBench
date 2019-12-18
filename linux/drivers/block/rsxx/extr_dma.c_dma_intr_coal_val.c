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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ INTR_COAL_COUNT_MASK ; 
 scalar_t__ INTR_COAL_COUNT_SHIFT ; 
 scalar_t__ INTR_COAL_LATENCY_MASK ; 
 scalar_t__ INTR_COAL_LATENCY_UNITS_NS ; 
 scalar_t__ RSXX_INTR_COAL_DISABLED ; 

__attribute__((used)) static u32 dma_intr_coal_val(u32 mode, u32 count, u32 latency)
{
	u32 latency_units = latency / INTR_COAL_LATENCY_UNITS_NS;

	if (mode == RSXX_INTR_COAL_DISABLED)
		return 0;

	return ((count << INTR_COAL_COUNT_SHIFT) & INTR_COAL_COUNT_MASK) |
			(latency_units & INTR_COAL_LATENCY_MASK);

}