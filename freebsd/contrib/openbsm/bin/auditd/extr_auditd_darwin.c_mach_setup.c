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
typedef  int /*<<< orphan*/  mach_msg_type_name_t ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_MSG_TYPE_MAKE_SEND ; 
 int /*<<< orphan*/  MACH_PORT_NULL ; 
 int /*<<< orphan*/  MACH_PORT_RIGHT_PORT_SET ; 
 int /*<<< orphan*/  MACH_PORT_RIGHT_RECEIVE ; 
 int /*<<< orphan*/  __AUDIT_LAUNCHD_LABEL ; 
 int /*<<< orphan*/  auditd_log_debug (char*) ; 
 int /*<<< orphan*/  auditd_log_err (char*) ; 
 int /*<<< orphan*/  control_port ; 
 scalar_t__ host_set_audit_control_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lookup_machport (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mach_host_self () ; 
 scalar_t__ mach_port_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mach_port_extract_right (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ mach_port_move_member (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mach_task_self () ; 
 int /*<<< orphan*/  port_set ; 
 int /*<<< orphan*/  signal_port ; 

__attribute__((used)) static int
mach_setup(int launchd_flag)
{
	mach_msg_type_name_t poly;

	/*
	 * Allocate a port set.
	 */
	if (mach_port_allocate(mach_task_self(), MACH_PORT_RIGHT_PORT_SET,
	    &port_set) != KERN_SUCCESS)  {
		auditd_log_err("Allocation of port set failed");
		return (-1);
	}


	/*
	 * Allocate a signal reflection port.
	 */
	if (mach_port_allocate(mach_task_self(), MACH_PORT_RIGHT_RECEIVE,
	    &signal_port) != KERN_SUCCESS ||
	    mach_port_move_member(mach_task_self(), signal_port, port_set) !=
	    KERN_SUCCESS)  {
		auditd_log_err("Allocation of signal port failed");
		return (-1);
	}

	/*
	 * Allocate a trigger port.
	 */
	if (launchd_flag) {
		/*
		 * If started under launchd, lookup port in launchd dictionary.
		 */
		if ((control_port = lookup_machport(__AUDIT_LAUNCHD_LABEL)) ==
		    MACH_PORT_NULL || mach_port_move_member(mach_task_self(),
		    control_port, port_set) != KERN_SUCCESS) {
			auditd_log_err("Cannot get Mach control port"
                            " via launchd");
			return (-1);
		} else
			auditd_log_debug("Mach control port registered"
			    " via launchd");
	} else {
		/*
		 * If not started under launchd, allocate port and register.
		 */
		if (mach_port_allocate(mach_task_self(),
		    MACH_PORT_RIGHT_RECEIVE, &control_port) != KERN_SUCCESS ||
		    mach_port_move_member(mach_task_self(), control_port,
		    port_set) != KERN_SUCCESS)
			auditd_log_err("Allocation of trigger port failed");

		/*
		 * Create a send right on our trigger port.
		 */
		mach_port_extract_right(mach_task_self(), control_port,
		    MACH_MSG_TYPE_MAKE_SEND, &control_port, &poly);

		/*
		 * Register the trigger port with the kernel.
		 */
		if (host_set_audit_control_port(mach_host_self(),
		    control_port) != KERN_SUCCESS) {
                        auditd_log_err("Cannot set Mach control port");
			return (-1);
		} else
			auditd_log_debug("Mach control port registered");
	}

	return (0);
}