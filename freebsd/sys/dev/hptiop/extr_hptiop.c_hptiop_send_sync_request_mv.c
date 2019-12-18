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
typedef  int u_int64_t ;
typedef  scalar_t__ u_int32_t ;
struct TYPE_2__ {int flags; } ;
struct hpt_iop_request_get_config {TYPE_1__ header; } ;
struct hpt_iop_hba {int ctlcfgcmd_phy; scalar_t__ config_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_RD4_MV0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int IOP_REQUEST_FLAG_OUTPUT_CONTEXT ; 
 int IOP_REQUEST_FLAG_SYNC_REQUEST ; 
 scalar_t__ MVIOP_MU_QUEUE_ADDR_HOST_BIT ; 
 int /*<<< orphan*/  hptiop_intr_mv (struct hpt_iop_hba*) ; 
 int /*<<< orphan*/  hptiop_mv_inbound_write (int,struct hpt_iop_hba*) ; 
 int /*<<< orphan*/  outbound_intmask ; 

__attribute__((used)) static int hptiop_send_sync_request_mv(struct hpt_iop_hba *hba,
					void *req, u_int32_t millisec)
{
	u_int32_t i;
	u_int64_t phy_addr;
	hba->config_done = 0;

	phy_addr = hba->ctlcfgcmd_phy |
			(u_int64_t)MVIOP_MU_QUEUE_ADDR_HOST_BIT;
	((struct hpt_iop_request_get_config *)req)->header.flags |=
		IOP_REQUEST_FLAG_SYNC_REQUEST |
		IOP_REQUEST_FLAG_OUTPUT_CONTEXT;
	hptiop_mv_inbound_write(phy_addr, hba);
	BUS_SPACE_RD4_MV0(outbound_intmask);

	for (i = 0; i < millisec; i++) {
		hptiop_intr_mv(hba);
		if (hba->config_done)
			return 0;
		DELAY(1000);
	}
	return -1;
}