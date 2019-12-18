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
struct bnxt_softc {int /*<<< orphan*/  hwrm_short_cmd_req_addr; int /*<<< orphan*/  hwrm_max_req_len; int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int iflib_dma_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnxt_alloc_hwrm_short_cmd_req(struct bnxt_softc *softc)
{
	int rc;

	rc = iflib_dma_alloc(softc->ctx, softc->hwrm_max_req_len,
	    &softc->hwrm_short_cmd_req_addr, BUS_DMA_NOWAIT);

	return rc;
}