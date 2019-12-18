#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int64_t ;
typedef  size_t u_int32_t ;
struct hpt_iop_request_header {int flags; int context; int type; int size; } ;
struct TYPE_5__ {int inlist_wptr; size_t list_count; TYPE_1__* inlist; } ;
struct TYPE_6__ {TYPE_2__ mvfrey; } ;
struct hpt_iop_hba {int ctlcfgcmd_phy; scalar_t__ config_done; TYPE_3__ u; } ;
struct TYPE_4__ {int addr; int intrfc_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_RD4_MVFREY2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUS_SPACE_WRT4_MVFREY2 (int /*<<< orphan*/ ,int) ; 
 int CL_POINTER_TOGGLE ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int IOPMU_QUEUE_ADDR_HOST_BIT ; 
 int IOP_REQUEST_FLAG_ADDR_BITS ; 
 int IOP_REQUEST_FLAG_OUTPUT_CONTEXT ; 
 int IOP_REQUEST_FLAG_SYNC_REQUEST ; 
 int /*<<< orphan*/  hptiop_intr_mvfrey (struct hpt_iop_hba*) ; 
 int /*<<< orphan*/  inbound_write_ptr ; 

__attribute__((used)) static int hptiop_send_sync_request_mvfrey(struct hpt_iop_hba *hba,
					void *req, u_int32_t millisec)
{
	u_int32_t i, index;
	u_int64_t phy_addr;
	struct hpt_iop_request_header *reqhdr =
										(struct hpt_iop_request_header *)req;
	
	hba->config_done = 0;

	phy_addr = hba->ctlcfgcmd_phy;
	reqhdr->flags = IOP_REQUEST_FLAG_SYNC_REQUEST
					| IOP_REQUEST_FLAG_OUTPUT_CONTEXT
					| IOP_REQUEST_FLAG_ADDR_BITS
					| ((phy_addr >> 16) & 0xffff0000);
	reqhdr->context = ((phy_addr & 0xffffffff) << 32 )
					| IOPMU_QUEUE_ADDR_HOST_BIT | reqhdr->type;

	hba->u.mvfrey.inlist_wptr++;
	index = hba->u.mvfrey.inlist_wptr & 0x3fff;

	if (index == hba->u.mvfrey.list_count) {
		index = 0;
		hba->u.mvfrey.inlist_wptr &= ~0x3fff;
		hba->u.mvfrey.inlist_wptr ^= CL_POINTER_TOGGLE;
	}

	hba->u.mvfrey.inlist[index].addr = phy_addr;
	hba->u.mvfrey.inlist[index].intrfc_len = (reqhdr->size + 3) / 4;

	BUS_SPACE_WRT4_MVFREY2(inbound_write_ptr, hba->u.mvfrey.inlist_wptr);
	BUS_SPACE_RD4_MVFREY2(inbound_write_ptr);

	for (i = 0; i < millisec; i++) {
		hptiop_intr_mvfrey(hba);
		if (hba->config_done)
			return 0;
		DELAY(1000);
	}
	return -1;
}