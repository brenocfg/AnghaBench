#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct kernel_ipmi_msg {int dummy; } ;
struct ipmi_user {int dummy; } ;
struct ipmi_addr {int dummy; } ;
struct TYPE_4__ {int* data; } ;
struct TYPE_5__ {TYPE_1__ msg; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dummy_count ; 
 TYPE_2__ halt_recv_msg ; 
 int /*<<< orphan*/  halt_smi_msg ; 
 int /*<<< orphan*/  ipmi_poll_interface (struct ipmi_user*) ; 
 int ipmi_request_supply_msgs (struct ipmi_user*,struct ipmi_addr*,int /*<<< orphan*/ ,struct kernel_ipmi_msg*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipmi_request_in_rc_mode(struct ipmi_user       *user,
				   struct ipmi_addr       *addr,
				   struct kernel_ipmi_msg *send_msg)
{
	int rv;

	atomic_set(&dummy_count, 2);
	rv = ipmi_request_supply_msgs(user, addr, 0, send_msg, NULL,
				      &halt_smi_msg, &halt_recv_msg, 0);
	if (rv) {
		atomic_set(&dummy_count, 0);
		return rv;
	}

	/*
	 * Spin until our message is done.
	 */
	while (atomic_read(&dummy_count) > 0) {
		ipmi_poll_interface(user);
		cpu_relax();
	}

	return halt_recv_msg.msg.data[0];
}