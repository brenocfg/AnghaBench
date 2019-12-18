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
 int EBUSY ; 
 int /*<<< orphan*/  IPMI_SET_TIMEOUT_FORCE_HB ; 
 int /*<<< orphan*/  IPMI_SET_TIMEOUT_NO_HB ; 
 int WDOG_PREOP_NONE ; 
 int /*<<< orphan*/  WDOG_TIMEOUT_NONE ; 
 int /*<<< orphan*/  WDOG_TIMEOUT_RESET ; 
 int /*<<< orphan*/  action_val ; 
 int ifnum_to_use ; 
 int ipmi_create_user (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ipmi_destroy_user (int /*<<< orphan*/ *) ; 
 int ipmi_get_version (int /*<<< orphan*/ *,int*,scalar_t__*) ; 
 int /*<<< orphan*/  ipmi_hndlrs ; 
 int ipmi_set_timeout (int /*<<< orphan*/ ) ; 
 int ipmi_version_major ; 
 scalar_t__ ipmi_version_minor ; 
 int /*<<< orphan*/  ipmi_watchdog_state ; 
 int /*<<< orphan*/  ipmi_wdog_miscdev ; 
 int misc_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ nmi_handler_registered ; 
 int /*<<< orphan*/  pr_crit (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 
 int preop_val ; 
 int pretimeout ; 
 scalar_t__ start_now ; 
 int testing_nmi ; 
 int timeout ; 
 int watchdog_ifnum ; 
 int /*<<< orphan*/ * watchdog_user ; 

__attribute__((used)) static void ipmi_register_watchdog(int ipmi_intf)
{
	int rv = -EBUSY;

	if (watchdog_user)
		goto out;

	if ((ifnum_to_use >= 0) && (ifnum_to_use != ipmi_intf))
		goto out;

	watchdog_ifnum = ipmi_intf;

	rv = ipmi_create_user(ipmi_intf, &ipmi_hndlrs, NULL, &watchdog_user);
	if (rv < 0) {
		pr_crit("Unable to register with ipmi\n");
		goto out;
	}

	rv = ipmi_get_version(watchdog_user,
			      &ipmi_version_major,
			      &ipmi_version_minor);
	if (rv) {
		pr_warn("Unable to get IPMI version, assuming 1.0\n");
		ipmi_version_major = 1;
		ipmi_version_minor = 0;
	}

	rv = misc_register(&ipmi_wdog_miscdev);
	if (rv < 0) {
		ipmi_destroy_user(watchdog_user);
		watchdog_user = NULL;
		pr_crit("Unable to register misc device\n");
	}

#ifdef HAVE_DIE_NMI
	if (nmi_handler_registered) {
		int old_pretimeout = pretimeout;
		int old_timeout = timeout;
		int old_preop_val = preop_val;

		/*
		 * Set the pretimeout to go off in a second and give
		 * ourselves plenty of time to stop the timer.
		 */
		ipmi_watchdog_state = WDOG_TIMEOUT_RESET;
		preop_val = WDOG_PREOP_NONE; /* Make sure nothing happens */
		pretimeout = 99;
		timeout = 100;

		testing_nmi = 1;

		rv = ipmi_set_timeout(IPMI_SET_TIMEOUT_FORCE_HB);
		if (rv) {
			pr_warn("Error starting timer to test NMI: 0x%x.  The NMI pretimeout will likely not work\n",
				rv);
			rv = 0;
			goto out_restore;
		}

		msleep(1500);

		if (testing_nmi != 2) {
			pr_warn("IPMI NMI didn't seem to occur.  The NMI pretimeout will likely not work\n");
		}
 out_restore:
		testing_nmi = 0;
		preop_val = old_preop_val;
		pretimeout = old_pretimeout;
		timeout = old_timeout;
	}
#endif

 out:
	if ((start_now) && (rv == 0)) {
		/* Run from startup, so start the timer now. */
		start_now = 0; /* Disable this function after first startup. */
		ipmi_watchdog_state = action_val;
		ipmi_set_timeout(IPMI_SET_TIMEOUT_FORCE_HB);
		pr_info("Starting now!\n");
	} else {
		/* Stop the timer now. */
		ipmi_watchdog_state = WDOG_TIMEOUT_NONE;
		ipmi_set_timeout(IPMI_SET_TIMEOUT_NO_HB);
	}
}