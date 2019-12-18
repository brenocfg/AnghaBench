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
struct dw_apb_clocksource {int dummy; } ;
struct clocksource {int dummy; } ;

/* Variables and functions */
 struct dw_apb_clocksource* clocksource_to_dw_apb_clocksource (struct clocksource*) ; 
 int /*<<< orphan*/  dw_apb_clocksource_start (struct dw_apb_clocksource*) ; 

__attribute__((used)) static void apbt_restart_clocksource(struct clocksource *cs)
{
	struct dw_apb_clocksource *dw_cs =
		clocksource_to_dw_apb_clocksource(cs);

	dw_apb_clocksource_start(dw_cs);
}