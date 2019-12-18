#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct bm_rcr {int busy; scalar_t__ pmode; int vbit; TYPE_1__* cursor; int /*<<< orphan*/  available; } ;
struct bm_portal {struct bm_rcr rcr; } ;
struct TYPE_2__ {int __dont_write_directly__verb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  RCR_INC (struct bm_rcr*) ; 
 int /*<<< orphan*/  RCR_PI_CINH ; 
 int /*<<< orphan*/  RCR_PTR2IDX (TYPE_1__*) ; 
 int /*<<< orphan*/  bm_out (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ e_BmPortalPCI ; 
 int /*<<< orphan*/  mb () ; 

void bm_rcr_pci_commit(struct bm_portal *portal, uint8_t myverb)
{
    register struct bm_rcr *rcr = &portal->rcr;
    ASSERT_COND(rcr->busy);
    ASSERT_COND(rcr->pmode == e_BmPortalPCI);
    rcr->cursor->__dont_write_directly__verb = (uint8_t)(myverb | rcr->vbit);
    RCR_INC(rcr);
    rcr->available--;
    mb();
    bm_out(RCR_PI_CINH, RCR_PTR2IDX(rcr->cursor));
#ifdef BM_CHECKING
    rcr->busy = 0;
#endif /* BM_CHECKING */
}