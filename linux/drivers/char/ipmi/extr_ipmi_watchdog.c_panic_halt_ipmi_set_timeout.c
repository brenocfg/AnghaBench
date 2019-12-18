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
 int __ipmi_set_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipmi_poll_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic_done_count ; 
 int /*<<< orphan*/  panic_halt_ipmi_heartbeat () ; 
 int /*<<< orphan*/  panic_halt_recv_msg ; 
 int /*<<< orphan*/  panic_halt_smi_msg ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  watchdog_user ; 

__attribute__((used)) static void panic_halt_ipmi_set_timeout(void)
{
	int send_heartbeat_now;
	int rv;

	/* Wait for the messages to be free. */
	while (atomic_read(&panic_done_count) != 0)
		ipmi_poll_interface(watchdog_user);
	atomic_add(1, &panic_done_count);
	rv = __ipmi_set_timeout(&panic_halt_smi_msg,
				&panic_halt_recv_msg,
				&send_heartbeat_now);
	if (rv) {
		atomic_sub(1, &panic_done_count);
		pr_warn("Unable to extend the watchdog timeout\n");
	} else {
		if (send_heartbeat_now)
			panic_halt_ipmi_heartbeat();
	}
	while (atomic_read(&panic_done_count) != 0)
		ipmi_poll_interface(watchdog_user);
}