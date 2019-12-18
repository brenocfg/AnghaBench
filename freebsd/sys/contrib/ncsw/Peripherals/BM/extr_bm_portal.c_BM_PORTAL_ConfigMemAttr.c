#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ t_Handle ;
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_3__ {int /*<<< orphan*/  hwExtStructsMemAttr; struct TYPE_3__* p_BmPortalDriverParams; } ;
typedef  TYPE_1__ t_BmPortal ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_1__*,int /*<<< orphan*/ ) ; 

t_Error BM_PORTAL_ConfigMemAttr(t_Handle h_BmPortal, uint32_t hwExtStructsMemAttr)
{
    t_BmPortal  *p_BmPortal = (t_BmPortal *)h_BmPortal;

    SANITY_CHECK_RETURN_ERROR(p_BmPortal, E_INVALID_HANDLE);
    SANITY_CHECK_RETURN_ERROR(p_BmPortal->p_BmPortalDriverParams, E_INVALID_HANDLE);

    p_BmPortal->p_BmPortalDriverParams->hwExtStructsMemAttr = hwExtStructsMemAttr;

    return E_OK;
}