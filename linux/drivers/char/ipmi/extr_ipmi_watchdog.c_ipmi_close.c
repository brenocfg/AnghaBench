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
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPMI_SET_TIMEOUT_NO_HB ; 
 scalar_t__ WATCHDOG_MINOR ; 
 int /*<<< orphan*/  WDOG_TIMEOUT_NONE ; 
 int /*<<< orphan*/  _ipmi_set_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int expect_close ; 
 scalar_t__ iminor (struct inode*) ; 
 int /*<<< orphan*/  ipmi_heartbeat () ; 
 int /*<<< orphan*/  ipmi_watchdog_mutex ; 
 int /*<<< orphan*/  ipmi_watchdog_state ; 
 int /*<<< orphan*/  ipmi_wdog_open ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_crit (char*) ; 

__attribute__((used)) static int ipmi_close(struct inode *ino, struct file *filep)
{
	if (iminor(ino) == WATCHDOG_MINOR) {
		if (expect_close == 42) {
			mutex_lock(&ipmi_watchdog_mutex);
			ipmi_watchdog_state = WDOG_TIMEOUT_NONE;
			_ipmi_set_timeout(IPMI_SET_TIMEOUT_NO_HB);
			mutex_unlock(&ipmi_watchdog_mutex);
		} else {
			pr_crit("Unexpected close, not stopping watchdog!\n");
			ipmi_heartbeat();
		}
		clear_bit(0, &ipmi_wdog_open);
	}

	expect_close = 0;

	return 0;
}