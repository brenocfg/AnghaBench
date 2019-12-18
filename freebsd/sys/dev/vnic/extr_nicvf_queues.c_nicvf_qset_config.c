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
struct TYPE_2__ {scalar_t__ cfg; int /*<<< orphan*/  num; int /*<<< orphan*/  msg; } ;
union nic_mbx {TYPE_1__ qs; } ;
struct queue_set {int /*<<< orphan*/  vnic_id; scalar_t__ enable; } ;
struct qs_cfg {int ena; int /*<<< orphan*/  vnic; } ;
struct nicvf {int /*<<< orphan*/  vf_id; int /*<<< orphan*/  dev; struct queue_set* qs; } ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  NIC_MBOX_MSG_QS_CFG ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nicvf_send_msg_to_pf (struct nicvf*,union nic_mbx*) ; 

void
nicvf_qset_config(struct nicvf *nic, boolean_t enable)
{
	union nic_mbx mbx = {};
	struct queue_set *qs;
	struct qs_cfg *qs_cfg;

	qs = nic->qs;
	if (qs == NULL) {
		device_printf(nic->dev,
		    "Qset is still not allocated, don't init queues\n");
		return;
	}

	qs->enable = enable;
	qs->vnic_id = nic->vf_id;

	/* Send a mailbox msg to PF to config Qset */
	mbx.qs.msg = NIC_MBOX_MSG_QS_CFG;
	mbx.qs.num = qs->vnic_id;

	mbx.qs.cfg = 0;
	qs_cfg = (struct qs_cfg *)&mbx.qs.cfg;
	if (qs->enable) {
		qs_cfg->ena = 1;
		qs_cfg->vnic = qs->vnic_id;
	}
	nicvf_send_msg_to_pf(nic, &mbx);
}