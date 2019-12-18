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
typedef  unsigned long u16 ;
struct nios2_timer {int dummy; } ;

/* Variables and functions */
 unsigned long ALTERA_TIMER_CONTROL_CONT_MSK ; 
 unsigned long ALTERA_TIMER_CONTROL_ITO_MSK ; 
 int /*<<< orphan*/  ALTERA_TIMER_CONTROL_REG ; 
 unsigned long ALTERA_TIMER_CONTROL_START_MSK ; 
 unsigned long ALTERA_TIMER_CONTROL_STOP_MSK ; 
 int /*<<< orphan*/  ALTERA_TIMER_PERIODH_REG ; 
 int /*<<< orphan*/  ALTERA_TIMER_PERIODL_REG ; 
 unsigned long timer_readw (struct nios2_timer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_writew (struct nios2_timer*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nios2_timer_config(struct nios2_timer *timer, unsigned long period,
			       bool periodic)
{
	u16 ctrl;

	/* The timer's actual period is one cycle greater than the value
	 * stored in the period register. */
	 period--;

	ctrl = timer_readw(timer, ALTERA_TIMER_CONTROL_REG);
	/* stop counter */
	timer_writew(timer, ctrl | ALTERA_TIMER_CONTROL_STOP_MSK,
		ALTERA_TIMER_CONTROL_REG);

	/* write new count */
	timer_writew(timer, period, ALTERA_TIMER_PERIODL_REG);
	timer_writew(timer, period >> 16, ALTERA_TIMER_PERIODH_REG);

	ctrl |= ALTERA_TIMER_CONTROL_START_MSK | ALTERA_TIMER_CONTROL_ITO_MSK;
	if (periodic)
		ctrl |= ALTERA_TIMER_CONTROL_CONT_MSK;
	else
		ctrl &= ~ALTERA_TIMER_CONTROL_CONT_MSK;
	timer_writew(timer, ctrl, ALTERA_TIMER_CONTROL_REG);
}