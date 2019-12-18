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
struct bm_rcr_entry {int dummy; } ;
struct bm_rcr {int busy; struct bm_rcr_entry* cursor; int /*<<< orphan*/  available; } ;
struct bm_portal {struct bm_rcr rcr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  dcbz_64 (struct bm_rcr_entry*) ; 

struct bm_rcr_entry *bm_rcr_start(struct bm_portal *portal)
{
    register struct bm_rcr *rcr = &portal->rcr;
    ASSERT_COND(!rcr->busy);
    if (!rcr->available)
        return NULL;
#ifdef BM_CHECKING
    rcr->busy = 1;
#endif /* BM_CHECKING */
    dcbz_64(rcr->cursor);
    return rcr->cursor;
}