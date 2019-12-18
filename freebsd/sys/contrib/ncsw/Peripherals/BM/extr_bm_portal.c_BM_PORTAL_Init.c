#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ t_Handle ;
typedef  scalar_t__ t_Error ;
struct TYPE_10__ {scalar_t__ irq; TYPE_2__* p_BmPortalLow; scalar_t__ cpu; TYPE_5__* p_BmPortalDriverParams; int /*<<< orphan*/  h_Bm; } ;
typedef  TYPE_3__ t_BmPortal ;
typedef  int /*<<< orphan*/  e_DpaaSwPortal ;
struct TYPE_11__ {int hwExtStructsMemAttr; int /*<<< orphan*/  mask; } ;
struct TYPE_8__ {int /*<<< orphan*/  addr_ci; int /*<<< orphan*/  addr_ce; } ;
struct TYPE_9__ {TYPE_1__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMAN_PORTAL_FLAG_CACHE ; 
 scalar_t__ BMAN_PORTAL_FLAG_IRQ ; 
 int /*<<< orphan*/  BM_PORTAL_Free (TYPE_3__*) ; 
 int /*<<< orphan*/  BmSetPortalHandle (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_NULL_POINTER ; 
 scalar_t__ E_OK ; 
 int /*<<< orphan*/  MAJOR ; 
 int MEMORY_ATTR_CACHEABLE ; 
 scalar_t__ NO_IRQ ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  XX_Free (TYPE_5__*) ; 
 scalar_t__ XX_VirtToPhys (int /*<<< orphan*/ ) ; 
 scalar_t__ bman_create_portal (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

t_Error BM_PORTAL_Init(t_Handle h_BmPortal)
{
    t_BmPortal          *p_BmPortal = (t_BmPortal *)h_BmPortal;
    uint32_t            flags;

    SANITY_CHECK_RETURN_ERROR(p_BmPortal, E_INVALID_HANDLE);

    flags = (uint32_t)((p_BmPortal->irq != NO_IRQ) ? BMAN_PORTAL_FLAG_IRQ : 0);
    flags |= ((p_BmPortal->p_BmPortalDriverParams->hwExtStructsMemAttr & MEMORY_ATTR_CACHEABLE) ?
           BMAN_PORTAL_FLAG_CACHE : 0);

    if (bman_create_portal(p_BmPortal,flags,&p_BmPortal->p_BmPortalDriverParams->mask)!=E_OK)
    {
        BM_PORTAL_Free(p_BmPortal);
        RETURN_ERROR(MAJOR, E_NULL_POINTER, ("create portal failed"));
    }
    BmSetPortalHandle(p_BmPortal->h_Bm, (t_Handle)p_BmPortal, (e_DpaaSwPortal)p_BmPortal->cpu);

    XX_Free(p_BmPortal->p_BmPortalDriverParams);
    p_BmPortal->p_BmPortalDriverParams = NULL;

    DBG(TRACE,("Bman-Portal (%d) @ %p:%p\n",
               p_BmPortal->cpu,
               p_BmPortal->p_BmPortalLow->addr.addr_ce,
               p_BmPortal->p_BmPortalLow->addr.addr_ci
               ));

    DBG(TRACE,("Bman-Portal (%d) @ 0x%016llx:0x%016llx",
               p_BmPortal->cpu,
               (uint64_t)XX_VirtToPhys(p_BmPortal->p_BmPortalLow->addr.addr_ce),
               (uint64_t)XX_VirtToPhys(p_BmPortal->p_BmPortalLow->addr.addr_ci)
               ));

    return E_OK;
}