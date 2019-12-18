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
 int /*<<< orphan*/  TIMER_CNTR2 ; 
 int /*<<< orphan*/  clock_lock ; 
 int i8254_freq ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 

void
timer_spkr_setfreq(int freq)
{

	freq = i8254_freq / freq;
	mtx_lock_spin(&clock_lock);
	outb(TIMER_CNTR2, freq & 0xff);
	outb(TIMER_CNTR2, freq >> 8);
	mtx_unlock_spin(&clock_lock);
}