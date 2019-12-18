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
typedef  unsigned long u64 ;
struct clock_event_device {int dummy; } ;
struct TYPE_2__ {unsigned long (* read ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  hv_init_timer (int /*<<< orphan*/ ,unsigned long) ; 
 TYPE_1__* hyperv_cs ; 
 unsigned long stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hv_ce_set_next_event(unsigned long delta,
				struct clock_event_device *evt)
{
	u64 current_tick;

	current_tick = hyperv_cs->read(NULL);
	current_tick += delta;
	hv_init_timer(0, current_tick);
	return 0;
}