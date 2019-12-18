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
struct clocksource {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprd_timer_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  suspend_to ; 
 int /*<<< orphan*/  timer_of_base (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sprd_suspend_timer_disable(struct clocksource *cs)
{
	sprd_timer_disable(timer_of_base(&suspend_to));
}