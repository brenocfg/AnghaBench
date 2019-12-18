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
struct timer8_priv {int dummy; } ;
struct clock_event_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct timer8_priv* ced_to_priv (struct clock_event_device*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer8_clock_event_start (struct timer8_priv*,int) ; 
 int /*<<< orphan*/  timer8_stop (struct timer8_priv*) ; 

__attribute__((used)) static int timer8_clock_event_oneshot(struct clock_event_device *ced)
{
	struct timer8_priv *p = ced_to_priv(ced);

	pr_info("%s: used for oneshot clock events\n", ced->name);
	timer8_stop(p);
	timer8_clock_event_start(p, 0x10000);

	return 0;
}