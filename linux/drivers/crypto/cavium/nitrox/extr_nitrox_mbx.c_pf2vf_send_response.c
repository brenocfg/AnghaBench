#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  vfid; int /*<<< orphan*/  chipid; } ;
union mbox_msg {scalar_t__ type; scalar_t__ value; TYPE_1__ id; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {int opcode; scalar_t__ value; int /*<<< orphan*/  data; } ;
struct nitrox_vfdev {int /*<<< orphan*/  mbx_resp; TYPE_2__ msg; int /*<<< orphan*/  ring; int /*<<< orphan*/  state; int /*<<< orphan*/  nr_queues; int /*<<< orphan*/  vfno; } ;
struct nitrox_device {int /*<<< orphan*/  idx; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 scalar_t__ MBX_MSG_TYPE_ACK ; 
 scalar_t__ MBX_MSG_TYPE_NOP ; 
#define  MSG_OP_CHIPID_VFID 131 
#define  MSG_OP_VF_DOWN 130 
#define  MSG_OP_VF_MODE 129 
#define  MSG_OP_VF_UP 128 
 int /*<<< orphan*/  __NDEV_NOT_READY ; 
 int /*<<< orphan*/  __NDEV_READY ; 
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pf2vf_write_mbox (struct nitrox_device*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pf2vf_send_response(struct nitrox_device *ndev,
				struct nitrox_vfdev *vfdev)
{
	union mbox_msg msg;

	msg.value = vfdev->msg.value;

	switch (vfdev->msg.opcode) {
	case MSG_OP_VF_MODE:
		msg.data = ndev->mode;
		break;
	case MSG_OP_VF_UP:
		vfdev->nr_queues = vfdev->msg.data;
		atomic_set(&vfdev->state, __NDEV_READY);
		break;
	case MSG_OP_CHIPID_VFID:
		msg.id.chipid = ndev->idx;
		msg.id.vfid = vfdev->vfno;
		break;
	case MSG_OP_VF_DOWN:
		vfdev->nr_queues = 0;
		atomic_set(&vfdev->state, __NDEV_NOT_READY);
		break;
	default:
		msg.type = MBX_MSG_TYPE_NOP;
		break;
	}

	if (msg.type == MBX_MSG_TYPE_NOP)
		return;

	/* send ACK to VF */
	msg.type = MBX_MSG_TYPE_ACK;
	pf2vf_write_mbox(ndev, msg.value, vfdev->ring);

	vfdev->msg.value = 0;
	atomic64_inc(&vfdev->mbx_resp);
}