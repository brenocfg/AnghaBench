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
typedef  scalar_t__ t_Handle ;
typedef  int /*<<< orphan*/  t_FmPcdCcTree ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNUSED (scalar_t__) ; 
 int /*<<< orphan*/  UpdateCcRootOwner (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

t_Error FmPcdCcUnbindTree(t_Handle h_FmPcd, t_Handle h_FmPcdCcTree)
{
    t_FmPcdCcTree *p_FmPcdCcTree = (t_FmPcdCcTree *)h_FmPcdCcTree;

    /* this routine must be protected by the calling routine by locking all PCD modules! */

    UNUSED(h_FmPcd);

    SANITY_CHECK_RETURN_ERROR(h_FmPcdCcTree, E_INVALID_HANDLE);

    UpdateCcRootOwner(p_FmPcdCcTree, FALSE);

    return E_OK;
}