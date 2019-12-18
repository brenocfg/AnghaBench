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
struct TYPE_2__ {int /*<<< orphan*/ * idi_vaddr; } ;
struct bnxt_softc {TYPE_1__ hwrm_short_cmd_req_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  iflib_dma_free (TYPE_1__*) ; 

__attribute__((used)) static void bnxt_free_hwrm_short_cmd_req(struct bnxt_softc *softc)
{
	if (softc->hwrm_short_cmd_req_addr.idi_vaddr)
		iflib_dma_free(&softc->hwrm_short_cmd_req_addr);
	softc->hwrm_short_cmd_req_addr.idi_vaddr = NULL;
}