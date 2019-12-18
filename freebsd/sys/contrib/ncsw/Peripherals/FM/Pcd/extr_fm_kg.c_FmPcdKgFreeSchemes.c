#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_5__ {TYPE_1__* schemesMng; struct TYPE_5__* p_FmPcdKg; } ;
typedef  TYPE_2__ t_FmPcd ;
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_4__ {size_t ownerId; scalar_t__ allocated; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int /*<<< orphan*/  E_OK ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_2__*,int /*<<< orphan*/ ) ; 

t_Error  FmPcdKgFreeSchemes(t_Handle h_FmPcd, uint8_t numOfSchemes, uint8_t guestId, uint8_t *p_SchemesIds)
{
    t_FmPcd             *p_FmPcd = (t_FmPcd *)h_FmPcd;
    uint8_t             i;

    SANITY_CHECK_RETURN_ERROR(p_FmPcd, E_INVALID_HANDLE);
    SANITY_CHECK_RETURN_ERROR(p_FmPcd->p_FmPcdKg, E_INVALID_HANDLE);

    /* This routine is issued only on master core of master partition -
       either directly or through IPC */

    for (i = 0; i < numOfSchemes; i++)
    {
        if (!p_FmPcd->p_FmPcdKg->schemesMng[p_SchemesIds[i]].allocated)
        {
            RETURN_ERROR(MAJOR, E_INVALID_STATE, ("Scheme was not previously allocated"));
        }
        if (p_FmPcd->p_FmPcdKg->schemesMng[p_SchemesIds[i]].ownerId != guestId)
        {
            RETURN_ERROR(MAJOR, E_INVALID_STATE, ("Scheme is not owned by caller. "));
        }
        p_FmPcd->p_FmPcdKg->schemesMng[p_SchemesIds[i]].allocated = FALSE;
        p_FmPcd->p_FmPcdKg->schemesMng[p_SchemesIds[i]].ownerId = 0;
    }

    return E_OK;
}