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
typedef  int uint32_t ;

/* Variables and functions */
 int CPU_TIMER_WD_AUTO ; 
 int CPU_TIMER_WD_EN ; 
 int mv_get_timer_control () ; 
 int /*<<< orphan*/  mv_set_timer_control (int) ; 
 int /*<<< orphan*/  mv_wdt_disable_armada_38x_xp_helper () ; 

__attribute__((used)) static void
mv_wdt_disable_armada_38x(void)
{
	uint32_t val;

	val = mv_get_timer_control();
	val &= ~(CPU_TIMER_WD_EN | CPU_TIMER_WD_AUTO);
	mv_set_timer_control(val);

	mv_wdt_disable_armada_38x_xp_helper();
}