#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ expires; scalar_t__ function; } ;

/* Variables and functions */
 scalar_t__ INPUT_POLL_TIME ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  panel_scan_timer ; 
 TYPE_1__ scan_timer ; 
 int /*<<< orphan*/  timer_setup (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_scan_timer(void)
{
	if (scan_timer.function)
		return;		/* already started */

	timer_setup(&scan_timer, panel_scan_timer, 0);
	scan_timer.expires = jiffies + INPUT_POLL_TIME;
	add_timer(&scan_timer);
}