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
struct ipmi_user {int dummy; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int ipmi_destroy_user (struct ipmi_user*) ; 
 int ipmi_start_timer_on_heartbeat ; 
 int /*<<< orphan*/  ipmi_watchdog_mutex ; 
 int /*<<< orphan*/  ipmi_wdog_miscdev ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_free_smi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_tofree ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int watchdog_ifnum ; 
 struct ipmi_user* watchdog_user ; 

__attribute__((used)) static void ipmi_unregister_watchdog(int ipmi_intf)
{
	int rv;
	struct ipmi_user *loc_user = watchdog_user;

	if (!loc_user)
		return;

	if (watchdog_ifnum != ipmi_intf)
		return;

	/* Make sure no one can call us any more. */
	misc_deregister(&ipmi_wdog_miscdev);

	watchdog_user = NULL;

	/*
	 * Wait to make sure the message makes it out.  The lower layer has
	 * pointers to our buffers, we want to make sure they are done before
	 * we release our memory.
	 */
	while (atomic_read(&msg_tofree))
		msg_free_smi(NULL);

	mutex_lock(&ipmi_watchdog_mutex);

	/* Disconnect from IPMI. */
	rv = ipmi_destroy_user(loc_user);
	if (rv)
		pr_warn("error unlinking from IPMI: %d\n",  rv);

	/* If it comes back, restart it properly. */
	ipmi_start_timer_on_heartbeat = 1;

	mutex_unlock(&ipmi_watchdog_mutex);
}