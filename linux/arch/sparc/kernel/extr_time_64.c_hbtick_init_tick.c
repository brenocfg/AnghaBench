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

/* Variables and functions */
 int /*<<< orphan*/  __hbird_read_stick () ; 
 int /*<<< orphan*/  __hbird_write_stick (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hbtick_disable_irq () ; 
 int /*<<< orphan*/  tick_disable_protection () ; 

__attribute__((used)) static void hbtick_init_tick(void)
{
	tick_disable_protection();

	/* XXX This seems to be necessary to 'jumpstart' Hummingbird
	 * XXX into actually sending STICK interrupts.  I think because
	 * XXX of how we store %tick_cmpr in head.S this somehow resets the
	 * XXX {TICK + STICK} interrupt mux.  -DaveM
	 */
	__hbird_write_stick(__hbird_read_stick());

	hbtick_disable_irq();
}