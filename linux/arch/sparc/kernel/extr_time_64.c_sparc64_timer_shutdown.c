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
struct TYPE_2__ {int /*<<< orphan*/  (* disable_irq ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 () ; 
 TYPE_1__ tick_operations ; 

__attribute__((used)) static int sparc64_timer_shutdown(struct clock_event_device *evt)
{
	tick_operations.disable_irq();
	return 0;
}