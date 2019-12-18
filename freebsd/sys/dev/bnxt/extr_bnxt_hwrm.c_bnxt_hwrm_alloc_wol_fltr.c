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
struct hwrm_wol_filter_alloc_output {int /*<<< orphan*/  wol_filter_id; } ;
struct hwrm_wol_filter_alloc_input {int /*<<< orphan*/  mac_address; int /*<<< orphan*/  enables; int /*<<< orphan*/  wol_type; int /*<<< orphan*/  port_id; int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {int /*<<< orphan*/  mac_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  port_id; } ;
struct TYPE_6__ {scalar_t__ idi_vaddr; } ;
struct bnxt_softc {int /*<<< orphan*/  wol_filter_id; TYPE_2__ func; TYPE_1__ pf; TYPE_3__ hwrm_cmd_resp; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  HWRM_WOL_FILTER_ALLOC ; 
 int /*<<< orphan*/  HWRM_WOL_FILTER_ALLOC_INPUT_ENABLES_MAC_ADDRESS ; 
 int /*<<< orphan*/  HWRM_WOL_FILTER_ALLOC_INPUT_WOL_TYPE_MAGICPKT ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt_softc*,struct hwrm_wol_filter_alloc_input*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 
 int hwrm_send_message (struct bnxt_softc*,struct hwrm_wol_filter_alloc_input*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
bnxt_hwrm_alloc_wol_fltr(struct bnxt_softc *softc)
{
	struct hwrm_wol_filter_alloc_input req = {0};
	struct hwrm_wol_filter_alloc_output *resp =
		(void *)softc->hwrm_cmd_resp.idi_vaddr;
	int rc;

	bnxt_hwrm_cmd_hdr_init(softc, &req, HWRM_WOL_FILTER_ALLOC);
	req.port_id = htole16(softc->pf.port_id);
	req.wol_type = HWRM_WOL_FILTER_ALLOC_INPUT_WOL_TYPE_MAGICPKT;
	req.enables =
		htole32(HWRM_WOL_FILTER_ALLOC_INPUT_ENABLES_MAC_ADDRESS);
	memcpy(req.mac_address, softc->func.mac_addr, ETHER_ADDR_LEN);
	rc = hwrm_send_message(softc, &req, sizeof(req));
	if (!rc)
		softc->wol_filter_id = resp->wol_filter_id;

	return rc;
}