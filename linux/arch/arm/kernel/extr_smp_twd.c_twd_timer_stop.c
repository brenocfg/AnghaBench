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
struct clock_event_device {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_percpu_irq (int /*<<< orphan*/ ) ; 
 struct clock_event_device* raw_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twd_evt ; 
 int /*<<< orphan*/  twd_shutdown (struct clock_event_device*) ; 

__attribute__((used)) static void twd_timer_stop(void)
{
	struct clock_event_device *clk = raw_cpu_ptr(twd_evt);

	twd_shutdown(clk);
	disable_percpu_irq(clk->irq);
}