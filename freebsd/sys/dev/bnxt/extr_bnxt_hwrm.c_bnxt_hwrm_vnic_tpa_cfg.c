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
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct hwrm_vnic_tpa_cfg_input {void* vnic_id; void* min_agg_len; void* max_aggs; void* max_agg_segs; void* enables; void* flags; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {scalar_t__ id; } ;
struct TYPE_3__ {scalar_t__ max_agg_segs; scalar_t__ max_aggs; int min_agg_len; scalar_t__ is_mode_gro; scalar_t__ enable; } ;
struct bnxt_softc {TYPE_2__ vnic_info; TYPE_1__ hw_lro; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 scalar_t__ HWRM_NA_SIGNATURE ; 
 int /*<<< orphan*/  HWRM_VNIC_TPA_CFG ; 
 int HWRM_VNIC_TPA_CFG_INPUT_ENABLES_MAX_AGGS ; 
 int HWRM_VNIC_TPA_CFG_INPUT_ENABLES_MAX_AGG_SEGS ; 
 int HWRM_VNIC_TPA_CFG_INPUT_ENABLES_MIN_AGG_LEN ; 
 int HWRM_VNIC_TPA_CFG_INPUT_FLAGS_AGG_WITH_ECN ; 
 int HWRM_VNIC_TPA_CFG_INPUT_FLAGS_AGG_WITH_SAME_GRE_SEQ ; 
 int HWRM_VNIC_TPA_CFG_INPUT_FLAGS_ENCAP_TPA ; 
 int HWRM_VNIC_TPA_CFG_INPUT_FLAGS_GRO ; 
 int HWRM_VNIC_TPA_CFG_INPUT_FLAGS_RSC_WND_UPDATE ; 
 int HWRM_VNIC_TPA_CFG_INPUT_FLAGS_TPA ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt_softc*,struct hwrm_vnic_tpa_cfg_input*,int /*<<< orphan*/ ) ; 
 void* htole16 (scalar_t__) ; 
 void* htole32 (int) ; 
 int hwrm_send_message (struct bnxt_softc*,struct hwrm_vnic_tpa_cfg_input*,int) ; 

int
bnxt_hwrm_vnic_tpa_cfg(struct bnxt_softc *softc)
{
	struct hwrm_vnic_tpa_cfg_input req = {0};
	uint32_t flags;

	if (softc->vnic_info.id == (uint16_t) HWRM_NA_SIGNATURE) {
		return 0;
	}

	bnxt_hwrm_cmd_hdr_init(softc, &req, HWRM_VNIC_TPA_CFG);

	if (softc->hw_lro.enable) {
		flags = HWRM_VNIC_TPA_CFG_INPUT_FLAGS_TPA |
			HWRM_VNIC_TPA_CFG_INPUT_FLAGS_ENCAP_TPA |
			HWRM_VNIC_TPA_CFG_INPUT_FLAGS_AGG_WITH_ECN |
			HWRM_VNIC_TPA_CFG_INPUT_FLAGS_AGG_WITH_SAME_GRE_SEQ;
		
        	if (softc->hw_lro.is_mode_gro)
			flags |= HWRM_VNIC_TPA_CFG_INPUT_FLAGS_GRO;
		else
			flags |= HWRM_VNIC_TPA_CFG_INPUT_FLAGS_RSC_WND_UPDATE;
			
		req.flags = htole32(flags);

		req.enables = htole32(HWRM_VNIC_TPA_CFG_INPUT_ENABLES_MAX_AGG_SEGS |
				HWRM_VNIC_TPA_CFG_INPUT_ENABLES_MAX_AGGS |
				HWRM_VNIC_TPA_CFG_INPUT_ENABLES_MIN_AGG_LEN);

		req.max_agg_segs = htole16(softc->hw_lro.max_agg_segs);
		req.max_aggs = htole16(softc->hw_lro.max_aggs);
		req.min_agg_len = htole32(softc->hw_lro.min_agg_len);
	}

	req.vnic_id = htole16(softc->vnic_info.id);

	return hwrm_send_message(softc, &req, sizeof(req));
}