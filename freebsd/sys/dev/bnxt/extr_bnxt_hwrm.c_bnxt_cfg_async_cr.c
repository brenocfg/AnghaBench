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
struct hwrm_func_vf_cfg_input {void* async_event_cr; void* enables; int /*<<< orphan*/  member_0; void* fid; } ;
struct hwrm_func_cfg_input {void* async_event_cr; void* enables; int /*<<< orphan*/  member_0; void* fid; } ;
struct TYPE_3__ {int phys_id; } ;
struct TYPE_4__ {TYPE_1__ ring; } ;
struct bnxt_softc {TYPE_2__ def_cp_ring; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 scalar_t__ BNXT_PF (struct bnxt_softc*) ; 
 int /*<<< orphan*/  HWRM_FUNC_CFG ; 
 int /*<<< orphan*/  HWRM_FUNC_CFG_INPUT_ENABLES_ASYNC_EVENT_CR ; 
 int /*<<< orphan*/  HWRM_FUNC_VF_CFG ; 
 int /*<<< orphan*/  HWRM_FUNC_VF_CFG_INPUT_ENABLES_ASYNC_EVENT_CR ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt_softc*,struct hwrm_func_vf_cfg_input*,int /*<<< orphan*/ ) ; 
 void* htole16 (int) ; 
 void* htole32 (int /*<<< orphan*/ ) ; 
 int hwrm_send_message (struct bnxt_softc*,struct hwrm_func_vf_cfg_input*,int) ; 

int
bnxt_cfg_async_cr(struct bnxt_softc *softc)
{
	int rc = 0;
	
	if (BNXT_PF(softc)) {
		struct hwrm_func_cfg_input req = {0};

		bnxt_hwrm_cmd_hdr_init(softc, &req, HWRM_FUNC_CFG);

		req.fid = htole16(0xffff);
		req.enables = htole32(HWRM_FUNC_CFG_INPUT_ENABLES_ASYNC_EVENT_CR);
		req.async_event_cr = htole16(softc->def_cp_ring.ring.phys_id);

		rc = hwrm_send_message(softc, &req, sizeof(req));
	}
	else {
		struct hwrm_func_vf_cfg_input req = {0};

		bnxt_hwrm_cmd_hdr_init(softc, &req, HWRM_FUNC_VF_CFG);

		req.enables = htole32(HWRM_FUNC_VF_CFG_INPUT_ENABLES_ASYNC_EVENT_CR);
		req.async_event_cr = htole16(softc->def_cp_ring.ring.phys_id);

		rc = hwrm_send_message(softc, &req, sizeof(req));
	}
	return rc;
}