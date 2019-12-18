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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static u32 cycle_timer_ticks(u32 cycle_timer)
{
	u32 ticks;

	ticks = cycle_timer & 0xfff;
	ticks += 3072 * ((cycle_timer >> 12) & 0x1fff);
	ticks += (3072 * 8000) * (cycle_timer >> 25);

	return ticks;
}