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
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hpet_enable_legacy_int () ; 
 int /*<<< orphan*/  hpet_print_config () ; 

__attribute__((used)) static int hpet_clkevt_legacy_resume(struct clock_event_device *evt)
{
	hpet_enable_legacy_int();
	hpet_print_config();
	return 0;
}