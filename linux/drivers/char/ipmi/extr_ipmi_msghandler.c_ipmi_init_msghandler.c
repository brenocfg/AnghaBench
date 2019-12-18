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
 scalar_t__ IPMI_TIMEOUT_JIFFIES ; 
 int /*<<< orphan*/  atomic_notifier_chain_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_srcu_struct (int /*<<< orphan*/ *) ; 
 int initialized ; 
 int /*<<< orphan*/  ipmi_interfaces_mutex ; 
 int /*<<< orphan*/  ipmi_interfaces_srcu ; 
 int ipmi_register_driver () ; 
 int /*<<< orphan*/  ipmi_timeout ; 
 int /*<<< orphan*/  ipmi_timer ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic_block ; 
 int /*<<< orphan*/  panic_notifier_list ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipmi_init_msghandler(void)
{
	int rv;

	mutex_lock(&ipmi_interfaces_mutex);
	rv = ipmi_register_driver();
	if (rv)
		goto out;
	if (initialized)
		goto out;

	init_srcu_struct(&ipmi_interfaces_srcu);

	timer_setup(&ipmi_timer, ipmi_timeout, 0);
	mod_timer(&ipmi_timer, jiffies + IPMI_TIMEOUT_JIFFIES);

	atomic_notifier_chain_register(&panic_notifier_list, &panic_block);

	initialized = true;

out:
	mutex_unlock(&ipmi_interfaces_mutex);
	return rv;
}