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
typedef  int uint32_t ;
struct hwrm_cfa_l2_filter_alloc_output {int /*<<< orphan*/  flow_id; int /*<<< orphan*/  l2_filter_id; } ;
struct hwrm_cfa_l2_filter_alloc_input {int /*<<< orphan*/  l2_addr_mask; int /*<<< orphan*/  l2_addr; int /*<<< orphan*/  dst_id; void* enables; void* flags; int /*<<< orphan*/  member_0; } ;
struct bnxt_vnic_info {int filter_id; void* flow_id; int /*<<< orphan*/  id; } ;
struct TYPE_2__ {scalar_t__ idi_vaddr; } ;
struct bnxt_softc {int /*<<< orphan*/  ctx; TYPE_1__ hwrm_cmd_resp; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_HWRM_LOCK (struct bnxt_softc*) ; 
 int /*<<< orphan*/  BNXT_HWRM_UNLOCK (struct bnxt_softc*) ; 
 int EDOOFUS ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  HWRM_CFA_L2_FILTER_ALLOC ; 
 int HWRM_CFA_L2_FILTER_ALLOC_INPUT_ENABLES_DST_ID ; 
 int HWRM_CFA_L2_FILTER_ALLOC_INPUT_ENABLES_L2_ADDR ; 
 int HWRM_CFA_L2_FILTER_ALLOC_INPUT_ENABLES_L2_ADDR_MASK ; 
 int HWRM_CFA_L2_FILTER_ALLOC_INPUT_FLAGS_PATH_RX ; 
 int _hwrm_send_message (struct bnxt_softc*,struct hwrm_cfa_l2_filter_alloc_input*,int) ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt_softc*,struct hwrm_cfa_l2_filter_alloc_input*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 void* htole32 (int) ; 
 int /*<<< orphan*/  if_getlladdr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_get_ifp (int /*<<< orphan*/ ) ; 
 void* le64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

int
bnxt_hwrm_set_filter(struct bnxt_softc *softc, struct bnxt_vnic_info *vnic)
{
	struct hwrm_cfa_l2_filter_alloc_input	req = {0};
	struct hwrm_cfa_l2_filter_alloc_output	*resp;
	uint32_t enables = 0;
	int rc = 0;

	if (vnic->filter_id != -1) {
		device_printf(softc->dev,
		    "Attempt to re-allocate l2 ctx filter\n");
		return EDOOFUS;
	}

	resp = (void *)softc->hwrm_cmd_resp.idi_vaddr;
	bnxt_hwrm_cmd_hdr_init(softc, &req, HWRM_CFA_L2_FILTER_ALLOC);

	req.flags = htole32(HWRM_CFA_L2_FILTER_ALLOC_INPUT_FLAGS_PATH_RX);
	enables = HWRM_CFA_L2_FILTER_ALLOC_INPUT_ENABLES_L2_ADDR
	    | HWRM_CFA_L2_FILTER_ALLOC_INPUT_ENABLES_L2_ADDR_MASK
	    | HWRM_CFA_L2_FILTER_ALLOC_INPUT_ENABLES_DST_ID;
	req.enables = htole32(enables);
	req.dst_id = htole16(vnic->id);
	memcpy(req.l2_addr, if_getlladdr(iflib_get_ifp(softc->ctx)),
	    ETHER_ADDR_LEN);
	memset(&req.l2_addr_mask, 0xff, sizeof(req.l2_addr_mask));

	BNXT_HWRM_LOCK(softc);
	rc = _hwrm_send_message(softc, &req, sizeof(req));
	if (rc)
		goto fail;

	vnic->filter_id = le64toh(resp->l2_filter_id);
	vnic->flow_id = le64toh(resp->flow_id);

fail:
	BNXT_HWRM_UNLOCK(softc);
	return (rc);
}