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
struct call {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIMER_STOP_CALL (struct call*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t301 ; 
 int /*<<< orphan*/  t303 ; 
 int /*<<< orphan*/  t308 ; 
 int /*<<< orphan*/  t310 ; 
 int /*<<< orphan*/  t313 ; 
 int /*<<< orphan*/  t322 ; 

__attribute__((used)) static void
reset_all_timers(struct call *c)
{
	TIMER_STOP_CALL(c, t301);
	TIMER_STOP_CALL(c, t303);
	TIMER_STOP_CALL(c, t308);
	TIMER_STOP_CALL(c, t310);
	TIMER_STOP_CALL(c, t313);
	TIMER_STOP_CALL(c, t322);
}