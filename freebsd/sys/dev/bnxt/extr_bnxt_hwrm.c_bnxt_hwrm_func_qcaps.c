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
struct hwrm_func_qcaps_output {int flags; int /*<<< orphan*/  max_rx_wm_flows; int /*<<< orphan*/  max_rx_em_flows; int /*<<< orphan*/  max_tx_wm_flows; int /*<<< orphan*/  max_tx_em_flows; int /*<<< orphan*/  max_decap_records; int /*<<< orphan*/  max_encap_records; int /*<<< orphan*/  max_vfs; int /*<<< orphan*/  first_vf_id; int /*<<< orphan*/  port_id; int /*<<< orphan*/  max_stat_ctx; int /*<<< orphan*/  max_vnics; int /*<<< orphan*/  max_l2_ctxs; int /*<<< orphan*/  max_hw_ring_grps; int /*<<< orphan*/  max_rx_rings; int /*<<< orphan*/  max_tx_rings; int /*<<< orphan*/  max_cmpl_rings; int /*<<< orphan*/  max_rsscos_ctx; int /*<<< orphan*/  mac_address; int /*<<< orphan*/  fid; } ;
struct hwrm_func_qcaps_input {int /*<<< orphan*/  fid; int /*<<< orphan*/  member_0; } ;
struct bnxt_pf_info {void* max_rx_wm_flows; void* max_rx_em_flows; void* max_tx_wm_flows; void* max_tx_em_flows; void* max_decap_records; void* max_encap_records; void* max_vfs; void* first_vf_id; void* port_id; } ;
struct bnxt_func_info {int /*<<< orphan*/  mac_addr; void* max_stat_ctxs; void* max_vnics; void* max_l2_ctxs; void* max_tx_rings; void* max_hw_ring_grps; void* max_rx_rings; void* max_cp_rings; void* max_rsscos_ctxs; void* fw_fid; } ;
struct TYPE_2__ {scalar_t__ idi_vaddr; } ;
struct bnxt_softc {int /*<<< orphan*/  dev; struct bnxt_pf_info pf; int /*<<< orphan*/  flags; struct bnxt_func_info func; TYPE_1__ hwrm_cmd_resp; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_FLAG_WOL_CAP ; 
 int /*<<< orphan*/  BNXT_HWRM_LOCK (struct bnxt_softc*) ; 
 int /*<<< orphan*/  BNXT_HWRM_UNLOCK (struct bnxt_softc*) ; 
 scalar_t__ BNXT_PF (struct bnxt_softc*) ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  HWRM_FUNC_QCAPS ; 
 int /*<<< orphan*/  HWRM_FUNC_QCAPS_OUTPUT_FLAGS_WOL_MAGICPKT_SUPPORTED ; 
 int _hwrm_send_message (struct bnxt_softc*,struct hwrm_func_qcaps_input*,int) ; 
 int /*<<< orphan*/  _is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt_softc*,struct hwrm_func_qcaps_input*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_random_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole16 (int) ; 
 int htole32 (int /*<<< orphan*/ ) ; 
 void* le16toh (int /*<<< orphan*/ ) ; 
 void* le32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
bnxt_hwrm_func_qcaps(struct bnxt_softc *softc)
{
	int rc = 0;
	struct hwrm_func_qcaps_input req = {0};
	struct hwrm_func_qcaps_output *resp =
	    (void *)softc->hwrm_cmd_resp.idi_vaddr;
	struct bnxt_func_info *func = &softc->func;

	bnxt_hwrm_cmd_hdr_init(softc, &req, HWRM_FUNC_QCAPS);
	req.fid = htole16(0xffff);

	BNXT_HWRM_LOCK(softc);
	rc = _hwrm_send_message(softc, &req, sizeof(req));
	if (rc)
		goto fail;

	if (resp->flags &
	    htole32(HWRM_FUNC_QCAPS_OUTPUT_FLAGS_WOL_MAGICPKT_SUPPORTED))
		softc->flags |= BNXT_FLAG_WOL_CAP;

	func->fw_fid = le16toh(resp->fid);
	memcpy(func->mac_addr, resp->mac_address, ETHER_ADDR_LEN);
	func->max_rsscos_ctxs = le16toh(resp->max_rsscos_ctx);
	func->max_cp_rings = le16toh(resp->max_cmpl_rings);
	func->max_tx_rings = le16toh(resp->max_tx_rings);
	func->max_rx_rings = le16toh(resp->max_rx_rings);
	func->max_hw_ring_grps = le32toh(resp->max_hw_ring_grps);
	if (!func->max_hw_ring_grps)
		func->max_hw_ring_grps = func->max_tx_rings;
	func->max_l2_ctxs = le16toh(resp->max_l2_ctxs);
	func->max_vnics = le16toh(resp->max_vnics);
	func->max_stat_ctxs = le16toh(resp->max_stat_ctx);
	if (BNXT_PF(softc)) {
		struct bnxt_pf_info *pf = &softc->pf;

		pf->port_id = le16toh(resp->port_id);
		pf->first_vf_id = le16toh(resp->first_vf_id);
		pf->max_vfs = le16toh(resp->max_vfs);
		pf->max_encap_records = le32toh(resp->max_encap_records);
		pf->max_decap_records = le32toh(resp->max_decap_records);
		pf->max_tx_em_flows = le32toh(resp->max_tx_em_flows);
		pf->max_tx_wm_flows = le32toh(resp->max_tx_wm_flows);
		pf->max_rx_em_flows = le32toh(resp->max_rx_em_flows);
		pf->max_rx_wm_flows = le32toh(resp->max_rx_wm_flows);
	}
	if (!_is_valid_ether_addr(func->mac_addr)) {
		device_printf(softc->dev, "Invalid ethernet address, generating random locally administered address\n");
		get_random_ether_addr(func->mac_addr);
	}

fail:
	BNXT_HWRM_UNLOCK(softc);
	return rc;
}