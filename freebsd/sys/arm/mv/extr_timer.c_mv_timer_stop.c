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
struct eventtimer {int dummy; } ;

/* Variables and functions */
 int CPU_TIMER0_AUTO ; 
 int CPU_TIMER0_EN ; 
 int mv_get_timer_control () ; 
 int /*<<< orphan*/  mv_set_timer_control (int) ; 

__attribute__((used)) static int
mv_timer_stop(struct eventtimer *et)
{
	uint32_t val;

	val = mv_get_timer_control();
	val &= ~(CPU_TIMER0_EN | CPU_TIMER0_AUTO);
	mv_set_timer_control(val);
	return (0);
}