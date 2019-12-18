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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {void* cdu_reserved; } ;
struct TYPE_3__ {void* cdu_usage; } ;
struct eth_context {TYPE_2__ xstorm_ag_context; TYPE_1__ ustorm_ag_context; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDU_REGION_NUMBER_UCM_AG ; 
 int /*<<< orphan*/  CDU_REGION_NUMBER_XCM_AG ; 
 void* CDU_RSRVD_VALUE_TYPE_A (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETH_CONNECTION_TYPE ; 
 int /*<<< orphan*/  HW_CID (struct bxe_softc*,int /*<<< orphan*/ ) ; 

void
bxe_set_ctx_validation(struct bxe_softc   *sc,
                       struct eth_context *cxt,
                       uint32_t           cid)
{
    /* ustorm cxt validation */
    cxt->ustorm_ag_context.cdu_usage =
        CDU_RSRVD_VALUE_TYPE_A(HW_CID(sc, cid),
            CDU_REGION_NUMBER_UCM_AG, ETH_CONNECTION_TYPE);
    /* xcontext validation */
    cxt->xstorm_ag_context.cdu_reserved =
        CDU_RSRVD_VALUE_TYPE_A(HW_CID(sc, cid),
            CDU_REGION_NUMBER_XCM_AG, ETH_CONNECTION_TYPE);
}