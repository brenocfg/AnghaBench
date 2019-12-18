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
struct bm_rcr {int /*<<< orphan*/  vbit; struct bm_rcr_entry* cursor; } ;

/* Variables and functions */
 int /*<<< orphan*/  BM_RCR_VERB_VBIT ; 
 struct bm_rcr_entry* RCR_CARRYCLEAR (struct bm_rcr_entry*) ; 

__attribute__((used)) static __inline__ void RCR_INC(struct bm_rcr *rcr)
{
    /* NB: this is odd-looking, but experiments show that it generates
     * fast code with essentially no branching overheads. We increment to
     * the next RCR pointer and handle overflow and 'vbit'. */
    struct bm_rcr_entry *partial = rcr->cursor + 1;
    rcr->cursor = RCR_CARRYCLEAR(partial);
    if (partial != rcr->cursor)
        rcr->vbit ^= BM_RCR_VERB_VBIT;
}