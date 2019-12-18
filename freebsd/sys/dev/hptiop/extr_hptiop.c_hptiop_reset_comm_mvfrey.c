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
typedef  int u_int32_t ;
struct TYPE_3__ {int inlist_phy; int outlist_phy; int outlist_cptr_phy; int inlist_wptr; int list_count; int* outlist_cptr; int outlist_rptr; } ;
struct TYPE_4__ {TYPE_1__ mvfrey; } ;
struct hpt_iop_hba {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_WRT4_MVFREY2 (int /*<<< orphan*/ ,int) ; 
 int CL_POINTER_TOGGLE ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  IOPMU_INBOUND_MSG0_RESET_COMM ; 
 scalar_t__ hptiop_send_sync_msg (struct hpt_iop_hba*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  inbound_base ; 
 int /*<<< orphan*/  inbound_base_high ; 
 int /*<<< orphan*/  outbound_base ; 
 int /*<<< orphan*/  outbound_base_high ; 
 int /*<<< orphan*/  outbound_shadow_base ; 
 int /*<<< orphan*/  outbound_shadow_base_high ; 

__attribute__((used)) static int hptiop_reset_comm_mvfrey(struct hpt_iop_hba *hba)
{
	u_int32_t i = 100;

	if (hptiop_send_sync_msg(hba, IOPMU_INBOUND_MSG0_RESET_COMM, 3000))
		return -1;

	/* wait 100ms for MCU ready */
	while(i--) {
		DELAY(1000);
	}

	BUS_SPACE_WRT4_MVFREY2(inbound_base,
							hba->u.mvfrey.inlist_phy & 0xffffffff);
	BUS_SPACE_WRT4_MVFREY2(inbound_base_high,
							(hba->u.mvfrey.inlist_phy >> 16) >> 16);

	BUS_SPACE_WRT4_MVFREY2(outbound_base,
							hba->u.mvfrey.outlist_phy & 0xffffffff);
	BUS_SPACE_WRT4_MVFREY2(outbound_base_high,
							(hba->u.mvfrey.outlist_phy >> 16) >> 16);

	BUS_SPACE_WRT4_MVFREY2(outbound_shadow_base,
							hba->u.mvfrey.outlist_cptr_phy & 0xffffffff);
	BUS_SPACE_WRT4_MVFREY2(outbound_shadow_base_high,
							(hba->u.mvfrey.outlist_cptr_phy >> 16) >> 16);

	hba->u.mvfrey.inlist_wptr = (hba->u.mvfrey.list_count - 1)
								| CL_POINTER_TOGGLE;
	*hba->u.mvfrey.outlist_cptr = (hba->u.mvfrey.list_count - 1)
								| CL_POINTER_TOGGLE;
	hba->u.mvfrey.outlist_rptr = hba->u.mvfrey.list_count - 1;
	
	return 0;
}