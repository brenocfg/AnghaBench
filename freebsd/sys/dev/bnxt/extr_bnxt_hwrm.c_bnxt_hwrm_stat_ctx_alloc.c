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
typedef  int /*<<< orphan*/  uint64_t ;
struct hwrm_stat_ctx_alloc_output {int /*<<< orphan*/  stat_ctx_id; } ;
struct hwrm_stat_ctx_alloc_input {int /*<<< orphan*/  stats_dma_addr; int /*<<< orphan*/  update_period_ms; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {scalar_t__ idi_vaddr; } ;
struct bnxt_softc {TYPE_1__ hwrm_cmd_resp; int /*<<< orphan*/  dev; } ;
struct bnxt_cp_ring {int /*<<< orphan*/  stats_ctx_id; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_HWRM_LOCK (struct bnxt_softc*) ; 
 int /*<<< orphan*/  BNXT_HWRM_UNLOCK (struct bnxt_softc*) ; 
 int EDOOFUS ; 
 int /*<<< orphan*/  HWRM_NA_SIGNATURE ; 
 int /*<<< orphan*/  HWRM_STAT_CTX_ALLOC ; 
 int _hwrm_send_message (struct bnxt_softc*,struct hwrm_stat_ctx_alloc_input*,int) ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt_softc*,struct hwrm_stat_ctx_alloc_input*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole32 (int) ; 
 int /*<<< orphan*/  htole64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32toh (int /*<<< orphan*/ ) ; 

int
bnxt_hwrm_stat_ctx_alloc(struct bnxt_softc *softc, struct bnxt_cp_ring *cpr,
    uint64_t paddr)
{
	struct hwrm_stat_ctx_alloc_input req = {0};
	struct hwrm_stat_ctx_alloc_output *resp;
	int rc = 0;

	if (cpr->stats_ctx_id != HWRM_NA_SIGNATURE) {
		device_printf(softc->dev,
		    "Attempt to re-allocate stats ctx %08x\n",
		    cpr->stats_ctx_id);
		return EDOOFUS;
	}

	resp = (void *)softc->hwrm_cmd_resp.idi_vaddr;
	bnxt_hwrm_cmd_hdr_init(softc, &req, HWRM_STAT_CTX_ALLOC);

	req.update_period_ms = htole32(1000);
	req.stats_dma_addr = htole64(paddr);

	BNXT_HWRM_LOCK(softc);
	rc = _hwrm_send_message(softc, &req, sizeof(req));
	if (rc)
		goto fail;

	cpr->stats_ctx_id = le32toh(resp->stat_ctx_id);

fail:
	BNXT_HWRM_UNLOCK(softc);

	return rc;
}