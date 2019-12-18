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
struct clock_event_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  enable; int /*<<< orphan*/  match; int /*<<< orphan*/  clear; } ;

/* Variables and functions */
 int TIMER_ENABLE ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ *) ; 
 TYPE_1__* rtos_timer ; 

__attribute__((used)) static int set_next_event(unsigned long delta, struct clock_event_device *evt)
{
	/*  Assuming the timer will be disabled when we enter here.  */

	iowrite32(1, &rtos_timer->clear);
	iowrite32(0, &rtos_timer->clear);

	iowrite32(delta, &rtos_timer->match);
	iowrite32(1 << TIMER_ENABLE, &rtos_timer->enable);
	return 0;
}