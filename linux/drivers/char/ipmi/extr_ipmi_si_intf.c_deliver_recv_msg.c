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
struct smi_info {int /*<<< orphan*/  intf; } ;
struct ipmi_smi_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipmi_smi_msg_received (int /*<<< orphan*/ ,struct ipmi_smi_msg*) ; 

__attribute__((used)) static void deliver_recv_msg(struct smi_info *smi_info,
			     struct ipmi_smi_msg *msg)
{
	/* Deliver the message to the upper layer. */
	ipmi_smi_msg_received(smi_info->intf, msg);
}