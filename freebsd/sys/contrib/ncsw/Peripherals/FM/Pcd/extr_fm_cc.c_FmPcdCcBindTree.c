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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_4__ {int /*<<< orphan*/  ccTreeBaseAddr; } ;
typedef  TYPE_1__ t_FmPcdCcTree ;
struct TYPE_5__ {scalar_t__ physicalMuramBase; } ;
typedef  TYPE_2__ t_FmPcd ;
typedef  scalar_t__ t_Error ;

/* Variables and functions */
 scalar_t__ CcUpdateParams (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 scalar_t__ E_OK ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UINT_TO_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UpdateCcRootOwner (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ XX_VirtToPhys (int /*<<< orphan*/ ) ; 

t_Error FmPcdCcBindTree(t_Handle h_FmPcd, t_Handle h_PcdParams,
                        t_Handle h_FmPcdCcTree, uint32_t *p_Offset,
                        t_Handle h_FmPort)
{
    t_FmPcd *p_FmPcd = (t_FmPcd*)h_FmPcd;
    t_FmPcdCcTree *p_FmPcdCcTree = (t_FmPcdCcTree *)h_FmPcdCcTree;
    t_Error err = E_OK;

    SANITY_CHECK_RETURN_ERROR(h_FmPcd, E_INVALID_HANDLE);
    SANITY_CHECK_RETURN_ERROR(h_FmPcdCcTree, E_INVALID_HANDLE);

    /* this routine must be protected by the calling routine by locking all PCD modules! */

    err = CcUpdateParams(h_FmPcd, h_PcdParams, h_FmPort, h_FmPcdCcTree, TRUE);

    if (err == E_OK)
        UpdateCcRootOwner(p_FmPcdCcTree, TRUE);

    *p_Offset = (uint32_t)(XX_VirtToPhys(
            UINT_TO_PTR(p_FmPcdCcTree->ccTreeBaseAddr))
            - p_FmPcd->physicalMuramBase);

    return err;
}