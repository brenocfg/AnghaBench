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
 scalar_t__ ACQUIRED ; 
 scalar_t__ RELEASED ; 
 int TIMER_16BIT ; 
 int /*<<< orphan*/  TIMER_MODE ; 
 int TIMER_SEL2 ; 
 int TIMER_SQWAVE ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ppi_spkr_on () ; 
 scalar_t__ timer2_state ; 

int
timer_spkr_acquire(void)
{
	int mode;

	mode = TIMER_SEL2 | TIMER_SQWAVE | TIMER_16BIT;

	if (timer2_state != RELEASED)
		return (-1);
	timer2_state = ACQUIRED;

	/*
	 * This access to the timer registers is as atomic as possible
	 * because it is a single instruction.  We could do better if we
	 * knew the rate.  Use of splclock() limits glitches to 10-100us,
	 * and this is probably good enough for timer2, so we aren't as
	 * careful with it as with timer0.
	 */
	outb(TIMER_MODE, TIMER_SEL2 | (mode & 0x3f));

	ppi_spkr_on();		/* enable counter2 output to speaker */
	return (0);
}