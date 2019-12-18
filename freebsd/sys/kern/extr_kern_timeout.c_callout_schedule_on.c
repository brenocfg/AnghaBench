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
struct callout {int /*<<< orphan*/  c_arg; int /*<<< orphan*/  c_func; } ;

/* Variables and functions */
 int callout_reset_on (struct callout*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
callout_schedule_on(struct callout *c, int to_ticks, int cpu)
{
	return callout_reset_on(c, to_ticks, c->c_func, c->c_arg, cpu);
}