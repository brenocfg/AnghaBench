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
struct hwrm_vnic_cfg_input {void* mru; void* lb_rule; void* cos_rule; void* rss_rule; void* dflt_ring_grp; void* vnic_id; int /*<<< orphan*/  enables; int /*<<< orphan*/  flags; int /*<<< orphan*/  member_0; } ;
struct bnxt_vnic_info {int flags; int /*<<< orphan*/  mru; int /*<<< orphan*/  lb_rule; int /*<<< orphan*/  cos_rule; int /*<<< orphan*/  rss_id; int /*<<< orphan*/  def_ring_grp; int /*<<< orphan*/  id; } ;
struct bnxt_softc {int dummy; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int BNXT_VNIC_FLAG_BD_STALL ; 
 int BNXT_VNIC_FLAG_DEFAULT ; 
 int BNXT_VNIC_FLAG_VLAN_STRIP ; 
 int /*<<< orphan*/  HWRM_VNIC_CFG ; 
 int HWRM_VNIC_CFG_INPUT_ENABLES_DFLT_RING_GRP ; 
 int HWRM_VNIC_CFG_INPUT_ENABLES_MRU ; 
 int HWRM_VNIC_CFG_INPUT_ENABLES_RSS_RULE ; 
 int HWRM_VNIC_CFG_INPUT_FLAGS_BD_STALL_MODE ; 
 int HWRM_VNIC_CFG_INPUT_FLAGS_DEFAULT ; 
 int HWRM_VNIC_CFG_INPUT_FLAGS_VLAN_STRIP_MODE ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt_softc*,struct hwrm_vnic_cfg_input*,int /*<<< orphan*/ ) ; 
 void* htole16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole32 (int) ; 
 int hwrm_send_message (struct bnxt_softc*,struct hwrm_vnic_cfg_input*,int) ; 

int
bnxt_hwrm_vnic_cfg(struct bnxt_softc *softc, struct bnxt_vnic_info *vnic)
{
	struct hwrm_vnic_cfg_input req = {0};

	bnxt_hwrm_cmd_hdr_init(softc, &req, HWRM_VNIC_CFG);

	if (vnic->flags & BNXT_VNIC_FLAG_DEFAULT)
		req.flags |= htole32(HWRM_VNIC_CFG_INPUT_FLAGS_DEFAULT);
	if (vnic->flags & BNXT_VNIC_FLAG_BD_STALL)
		req.flags |= htole32(HWRM_VNIC_CFG_INPUT_FLAGS_BD_STALL_MODE);
	if (vnic->flags & BNXT_VNIC_FLAG_VLAN_STRIP)
		req.flags |= htole32(HWRM_VNIC_CFG_INPUT_FLAGS_VLAN_STRIP_MODE);
	req.enables = htole32(HWRM_VNIC_CFG_INPUT_ENABLES_DFLT_RING_GRP |
	    HWRM_VNIC_CFG_INPUT_ENABLES_RSS_RULE |
	    HWRM_VNIC_CFG_INPUT_ENABLES_MRU);
	req.vnic_id = htole16(vnic->id);
	req.dflt_ring_grp = htole16(vnic->def_ring_grp);
	req.rss_rule = htole16(vnic->rss_id);
	req.cos_rule = htole16(vnic->cos_rule);
	req.lb_rule = htole16(vnic->lb_rule);
	req.mru = htole16(vnic->mru);

	return hwrm_send_message(softc, &req, sizeof(req));
}