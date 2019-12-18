#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ t_Handle ;
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_4__ {scalar_t__ cpu; int /*<<< orphan*/  h_Bm; } ;
typedef  TYPE_1__ t_BmPortal ;
typedef  int /*<<< orphan*/  e_DpaaSwPortal ;

/* Variables and functions */
 int /*<<< orphan*/  BmSetPortalHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  XX_Free (TYPE_1__*) ; 
 int /*<<< orphan*/  bman_destroy_portal (TYPE_1__*) ; 

t_Error BM_PORTAL_Free(t_Handle h_BmPortal)
{
    t_BmPortal  *p_BmPortal = (t_BmPortal *)h_BmPortal;

    if (!p_BmPortal)
       return ERROR_CODE(E_INVALID_HANDLE);
    BmSetPortalHandle(p_BmPortal->h_Bm, NULL, (e_DpaaSwPortal)p_BmPortal->cpu);
    bman_destroy_portal(p_BmPortal);
    XX_Free(p_BmPortal);
    return E_OK;
}