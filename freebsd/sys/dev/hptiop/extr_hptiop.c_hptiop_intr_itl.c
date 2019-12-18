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
 int BUS_SPACE_RD4_ITL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUS_SPACE_WRT4_ITL (int /*<<< orphan*/ ,int) ; 
 int IOPMU_OUTBOUND_INT_MSG0 ; 
 int IOPMU_OUTBOUND_INT_POSTQUEUE ; 
 int /*<<< orphan*/  KdPrint (char*) ; 
 int /*<<< orphan*/  hptiop_drain_outbound_queue_itl (struct hpt_iop_hba*) ; 
 int /*<<< orphan*/  hptiop_os_message_callback (struct hpt_iop_hba*,int) ; 
 int /*<<< orphan*/  outbound_intstatus ; 
 int /*<<< orphan*/  outbound_msgaddr0 ; 

__attribute__((used)) static int hptiop_intr_itl(struct hpt_iop_hba * hba)
{
	u_int32_t status;
	int ret = 0;

	status = BUS_SPACE_RD4_ITL(outbound_intstatus);

	if (status & IOPMU_OUTBOUND_INT_MSG0) {
		u_int32_t msg = BUS_SPACE_RD4_ITL(outbound_msgaddr0);
		KdPrint(("hptiop: received outbound msg %x\n", msg));
		BUS_SPACE_WRT4_ITL(outbound_intstatus, IOPMU_OUTBOUND_INT_MSG0);
		hptiop_os_message_callback(hba, msg);
		ret = 1;
	}

	if (status & IOPMU_OUTBOUND_INT_POSTQUEUE) {
		hptiop_drain_outbound_queue_itl(hba);
		ret = 1;
	}

	return ret;
}