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
struct ipmi_smi {int dummy; } ;
struct ipmi_recv_msg {int dummy; } ;

/* Variables and functions */
 scalar_t__ deliver_response (struct ipmi_smi*,struct ipmi_recv_msg*) ; 
 int /*<<< orphan*/  handled_local_responses ; 
 int /*<<< orphan*/  ipmi_inc_stat (struct ipmi_smi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unhandled_local_responses ; 

__attribute__((used)) static void deliver_local_response(struct ipmi_smi *intf,
				   struct ipmi_recv_msg *msg)
{
	if (deliver_response(intf, msg))
		ipmi_inc_stat(intf, unhandled_local_responses);
	else
		ipmi_inc_stat(intf, handled_local_responses);
}