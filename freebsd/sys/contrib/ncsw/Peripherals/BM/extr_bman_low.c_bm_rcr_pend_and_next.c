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
typedef  int uint8_t ;
struct bm_rcr_entry {int __dont_write_directly__verb; } ;
struct bm_rcr {int busy; scalar_t__ pmode; int available; int vbit; struct bm_rcr_entry* cursor; } ;
struct bm_portal {struct bm_rcr rcr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  RCR_INC (struct bm_rcr*) ; 
 int /*<<< orphan*/  dcbf_64 (struct bm_rcr_entry*) ; 
 int /*<<< orphan*/  dcbz_64 (struct bm_rcr_entry*) ; 
 scalar_t__ e_BmPortalPVB ; 

struct bm_rcr_entry *bm_rcr_pend_and_next(struct bm_portal *portal, uint8_t myverb)
{
    register struct bm_rcr *rcr = &portal->rcr;
    ASSERT_COND(rcr->busy);
    ASSERT_COND(rcr->pmode != e_BmPortalPVB);
    if (rcr->available == 1)
        return NULL;
    rcr->cursor->__dont_write_directly__verb = (uint8_t)(myverb | rcr->vbit);
    dcbf_64(rcr->cursor);
    RCR_INC(rcr);
    rcr->available--;
    dcbz_64(rcr->cursor);
    return rcr->cursor;
}