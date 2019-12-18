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
typedef  int u_int32_t ;
struct hpt_iop_hba {int dummy; } ;

/* Variables and functions */
 int BUS_SPACE_RD4_MV0 (int /*<<< orphan*/ ) ; 
 int BUS_SPACE_RD4_MV2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUS_SPACE_WRT4_MV0 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KdPrint (char*) ; 
 int MVIOP_MU_OUTBOUND_INT_MSG ; 
 int MVIOP_MU_OUTBOUND_INT_POSTQUEUE ; 
 int /*<<< orphan*/  hptiop_drain_outbound_queue_mv (struct hpt_iop_hba*) ; 
 int /*<<< orphan*/  hptiop_os_message_callback (struct hpt_iop_hba*,int) ; 
 int /*<<< orphan*/  outbound_doorbell ; 
 int /*<<< orphan*/  outbound_msg ; 

__attribute__((used)) static int hptiop_intr_mv(struct hpt_iop_hba * hba)
{
	u_int32_t status;
	int ret = 0;

	status = BUS_SPACE_RD4_MV0(outbound_doorbell);

	if (status)
		BUS_SPACE_WRT4_MV0(outbound_doorbell, ~status);

	if (status & MVIOP_MU_OUTBOUND_INT_MSG) {
		u_int32_t msg = BUS_SPACE_RD4_MV2(outbound_msg);
		KdPrint(("hptiop: received outbound msg %x\n", msg));
		hptiop_os_message_callback(hba, msg);
		ret = 1;
	}

	if (status & MVIOP_MU_OUTBOUND_INT_POSTQUEUE) {
		hptiop_drain_outbound_queue_mv(hba);
		ret = 1;
	}

	return ret;
}