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
struct TYPE_4__ {int flags; int /*<<< orphan*/  p_BmPortalLow; int /*<<< orphan*/  irq; } ;
typedef  TYPE_1__ t_BmPortal ;

/* Variables and functions */
 int BMAN_PORTAL_FLAG_IRQ ; 
 int /*<<< orphan*/  BM_RCR_RING ; 
 int /*<<< orphan*/  BmUpdate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XX_DisableIntr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XX_Free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XX_FreeIntr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bm_mc_finish (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bm_rcr_finish (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bman_destroy_portal(t_BmPortal* p_BmPortal)
{
    BmUpdate(p_BmPortal, BM_RCR_RING);
    if (p_BmPortal->flags & BMAN_PORTAL_FLAG_IRQ)
    {
        XX_DisableIntr(p_BmPortal->irq);
        XX_FreeIntr(p_BmPortal->irq);
    }
    bm_mc_finish(p_BmPortal->p_BmPortalLow);
    bm_rcr_finish(p_BmPortal->p_BmPortalLow);
    XX_Free(p_BmPortal->p_BmPortalLow);
}