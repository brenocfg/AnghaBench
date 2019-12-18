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
struct TYPE_2__ {int msg; } ;
union nic_mbx {TYPE_1__ msg; } ;
struct nicvf {int /*<<< orphan*/  vf_id; int /*<<< orphan*/  dev; void* pf_acked; void* pf_nacked; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int EBUSY ; 
 int EINVAL ; 
 void* FALSE ; 
 int /*<<< orphan*/  NICVF_CORE_LOCK_ASSERT (struct nicvf*) ; 
 int NIC_MBOX_MSG_TIMEOUT ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nicvf_write_to_mbx (struct nicvf*,union nic_mbx*) ; 

int
nicvf_send_msg_to_pf(struct nicvf *nic, union nic_mbx *mbx)
{
	int timeout = NIC_MBOX_MSG_TIMEOUT * 10;
	int sleep = 2;

	NICVF_CORE_LOCK_ASSERT(nic);

	nic->pf_acked = FALSE;
	nic->pf_nacked = FALSE;

	nicvf_write_to_mbx(nic, mbx);

	/* Wait for previous message to be acked, timeout 2sec */
	while (!nic->pf_acked) {
		if (nic->pf_nacked)
			return (EINVAL);

		DELAY(sleep * 1000);

		if (nic->pf_acked)
			break;
		timeout -= sleep;
		if (!timeout) {
			device_printf(nic->dev,
				   "PF didn't ack to mbox msg %d from VF%d\n",
				   (mbx->msg.msg & 0xFF), nic->vf_id);

			return (EBUSY);
		}
	}
	return (0);
}