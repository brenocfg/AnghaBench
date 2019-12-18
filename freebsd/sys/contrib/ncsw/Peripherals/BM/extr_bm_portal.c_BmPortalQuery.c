#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ t_Handle ;
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_11__ {int /*<<< orphan*/  p_BmPortalLow; } ;
typedef  TYPE_4__ t_BmPortal ;
struct bman_depletion {int dummy; } ;
struct TYPE_8__ {struct bman_depletion state; } ;
struct TYPE_10__ {struct bman_depletion state; } ;
struct TYPE_9__ {TYPE_1__ as; TYPE_3__ ds; } ;
struct bm_mc_result {TYPE_2__ query; } ;

/* Variables and functions */
 int /*<<< orphan*/  BM_MCC_VERB_CMD_QUERY ; 
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  NCSW_PLOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  PUNLOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bm_mc_commit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bm_mc_result* bm_mc_result (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bm_mc_start (int /*<<< orphan*/ ) ; 

t_Error BmPortalQuery(t_Handle h_BmPortal, struct bman_depletion *p_Pools, bool depletion)
{
    t_BmPortal          *p_BmPortal = (t_BmPortal *)h_BmPortal;
    struct bm_mc_result *mcr;

    SANITY_CHECK_RETURN_ERROR(p_BmPortal, E_INVALID_HANDLE);

    NCSW_PLOCK(p_BmPortal);
    bm_mc_start(p_BmPortal->p_BmPortalLow);
    bm_mc_commit(p_BmPortal->p_BmPortalLow, BM_MCC_VERB_CMD_QUERY);
    while (!(mcr = bm_mc_result(p_BmPortal->p_BmPortalLow))) ;
    if (depletion)
        *p_Pools = mcr->query.ds.state;
    else
        *p_Pools = mcr->query.as.state;
    PUNLOCK(p_BmPortal);
    return E_OK;
}