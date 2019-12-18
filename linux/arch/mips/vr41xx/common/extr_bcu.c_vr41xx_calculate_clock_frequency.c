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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 unsigned long calculate_pclock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calculate_tclock (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calculate_vtclock (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  read_clkspeed () ; 
 int /*<<< orphan*/  vr41xx_tclock ; 
 int /*<<< orphan*/  vr41xx_vtclock ; 

void vr41xx_calculate_clock_frequency(void)
{
	unsigned long pclock;
	uint16_t clkspeed;

	clkspeed = read_clkspeed();

	pclock = calculate_pclock(clkspeed);
	vr41xx_vtclock = calculate_vtclock(clkspeed, pclock);
	vr41xx_tclock = calculate_tclock(clkspeed, pclock, vr41xx_vtclock);
}