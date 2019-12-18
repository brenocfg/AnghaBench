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
 int /*<<< orphan*/  cur_fd ; 
 int first_stop ; 
 int /*<<< orphan*/  report_stop () ; 
 scalar_t__ response_pending () ; 
 int /*<<< orphan*/  send_pending_data (int /*<<< orphan*/ ) ; 
 int stop_pending ; 
 int stopped_vcpu ; 

__attribute__((used)) static void
gdb_finish_suspend_vcpus(void)
{

	if (first_stop) {
		first_stop = false;
		stopped_vcpu = -1;
	} else if (response_pending())
		stop_pending = true;
	else {
		report_stop();
		send_pending_data(cur_fd);
	}
}