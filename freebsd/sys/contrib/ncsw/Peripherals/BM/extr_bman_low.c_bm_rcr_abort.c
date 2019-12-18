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
struct bm_rcr {scalar_t__ busy; } ;
struct bm_portal {struct bm_rcr rcr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (scalar_t__) ; 
 int /*<<< orphan*/  UNUSED (struct bm_rcr*) ; 

void bm_rcr_abort(struct bm_portal *portal)
{
    register struct bm_rcr *rcr = &portal->rcr;
    ASSERT_COND(rcr->busy);
#ifdef BM_CHECKING
    rcr->busy = 0;
#else
    UNUSED(rcr);
#endif /* BM_CHECKING */
}