#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  msg; } ;
union nic_mbx {TYPE_1__ msg; } ;
struct nicpf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NIC_MBOX_MSG_NACK ; 
 int /*<<< orphan*/  nic_send_msg_to_vf (struct nicpf*,int,union nic_mbx*) ; 

__attribute__((used)) static void
nic_mbx_send_nack(struct nicpf *nic, int vf)
{
	union nic_mbx mbx = {};

	mbx.msg.msg = NIC_MBOX_MSG_NACK;
	nic_send_msg_to_vf(nic, vf, &mbx);
}