#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  fdFqDrop; struct TYPE_5__* p_QmPortalDriverParams; int /*<<< orphan*/  fdFqHighPri; int /*<<< orphan*/  fdFq; int /*<<< orphan*/  dqrrHighPri; int /*<<< orphan*/  dqrr; int /*<<< orphan*/  eqcrHighPri; int /*<<< orphan*/  eqcr; int /*<<< orphan*/  fdFqLiodn; int /*<<< orphan*/  dqrrLiodn; int /*<<< orphan*/  stashDestQueue; } ;
typedef  TYPE_1__ t_QmPortalStashParam ;
typedef  TYPE_1__ t_QmPortal ;
typedef  scalar_t__ t_Handle ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_NULL_POINTER ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_1__*,int /*<<< orphan*/ ) ; 

t_Error QM_PORTAL_ConfigStash(t_Handle h_QmPortal, t_QmPortalStashParam *p_StashParams)
{
    t_QmPortal  *p_QmPortal = (t_QmPortal *)h_QmPortal;

    SANITY_CHECK_RETURN_ERROR(p_QmPortal, E_INVALID_HANDLE);
    SANITY_CHECK_RETURN_ERROR(p_QmPortal->p_QmPortalDriverParams, E_NULL_POINTER);
    SANITY_CHECK_RETURN_ERROR(p_StashParams, E_NULL_POINTER);

    p_QmPortal->p_QmPortalDriverParams->stashDestQueue  = p_StashParams->stashDestQueue;
    p_QmPortal->p_QmPortalDriverParams->dqrrLiodn       = p_StashParams->dqrrLiodn;
    p_QmPortal->p_QmPortalDriverParams->fdFqLiodn       = p_StashParams->fdFqLiodn;
    p_QmPortal->p_QmPortalDriverParams->eqcr            = p_StashParams->eqcr;
    p_QmPortal->p_QmPortalDriverParams->eqcrHighPri     = p_StashParams->eqcrHighPri;
    p_QmPortal->p_QmPortalDriverParams->dqrr            = p_StashParams->dqrr;
    p_QmPortal->p_QmPortalDriverParams->dqrrHighPri     = p_StashParams->dqrrHighPri;
    p_QmPortal->p_QmPortalDriverParams->fdFq            = p_StashParams->fdFq;
    p_QmPortal->p_QmPortalDriverParams->fdFqHighPri     = p_StashParams->fdFqHighPri;
    p_QmPortal->p_QmPortalDriverParams->fdFqDrop        = p_StashParams->fdFqDrop;

    return E_OK;
}