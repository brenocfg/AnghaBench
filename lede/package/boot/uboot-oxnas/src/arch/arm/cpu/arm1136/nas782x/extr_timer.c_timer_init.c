#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_3__ {scalar_t__ tbl; int /*<<< orphan*/  lastinc; } ;
struct TYPE_4__ {TYPE_1__ arch; } ;

/* Variables and functions */
 scalar_t__ CONFIG_SYS_TIMERBASE ; 
 int CONFIG_TIMER_PRESCALE ; 
 int /*<<< orphan*/  READ_TIMER ; 
 scalar_t__ TIMER_CTRL ; 
 int TIMER_ENABLE ; 
 int TIMER_ENABLE_SHIFT ; 
 scalar_t__ TIMER_LOAD ; 
 int TIMER_LOAD_VAL ; 
 int TIMER_MODE_PERIODIC ; 
 int TIMER_MODE_SHIFT ; 
 int TIMER_PRESCALE_SHIFT ; 
 TYPE_2__* gd ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

int timer_init (void)
{
	int32_t val;

	/* Start the counter ticking up */
	writel(TIMER_LOAD_VAL, CONFIG_SYS_TIMERBASE + TIMER_LOAD);	/* reload value on overflow*/

	val = (CONFIG_TIMER_PRESCALE << TIMER_PRESCALE_SHIFT) |
			(TIMER_MODE_PERIODIC << TIMER_MODE_SHIFT) |
			(TIMER_ENABLE << TIMER_ENABLE_SHIFT);		/* mask to enable timer*/
	writel(val, CONFIG_SYS_TIMERBASE + TIMER_CTRL);	/* start timer */

	/* reset time */
	gd->arch.lastinc = READ_TIMER;	/* capture current incrementer value */
	gd->arch.tbl = 0;		/* start "advancing" time stamp */

	return(0);
}