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
typedef  int uint32_t ;

/* Variables and functions */
 int NUM_OF_HPTSI_SLOTS ; 

__attribute__((used)) static inline int
tick_to_wheel(uint32_t cts_in_wticks)
{
	/* 
	 * Given a timestamp in wheel ticks (10usec inc's)
	 * map it to our limited space wheel.
	 */
	return (cts_in_wticks % NUM_OF_HPTSI_SLOTS);
}