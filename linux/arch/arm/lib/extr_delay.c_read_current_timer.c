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
struct TYPE_2__ {unsigned long (* read_current_timer ) () ;} ;

/* Variables and functions */
 int ENXIO ; 
 TYPE_1__* delay_timer ; 
 unsigned long stub1 () ; 

int read_current_timer(unsigned long *timer_val)
{
	if (!delay_timer)
		return -ENXIO;

	*timer_val = delay_timer->read_current_timer();
	return 0;
}