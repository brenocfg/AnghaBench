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
 int _ipmi_set_timeout (int) ; 
 int /*<<< orphan*/  ipmi_watchdog_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipmi_set_timeout(int do_heartbeat)
{
	int rv;

	mutex_lock(&ipmi_watchdog_mutex);
	rv = _ipmi_set_timeout(do_heartbeat);
	mutex_unlock(&ipmi_watchdog_mutex);

	return rv;
}