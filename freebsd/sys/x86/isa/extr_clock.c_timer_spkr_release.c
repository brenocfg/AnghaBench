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
 int /*<<< orphan*/  ppi_spkr_off () ; 
 scalar_t__ timer2_state ; 

int
timer_spkr_release(void)
{

	if (timer2_state != ACQUIRED)
		return (-1);
	timer2_state = RELEASED;
	outb(TIMER_MODE, TIMER_SEL2 | TIMER_SQWAVE | TIMER_16BIT);

	ppi_spkr_off();		/* disable counter2 output to speaker */
	return (0);
}