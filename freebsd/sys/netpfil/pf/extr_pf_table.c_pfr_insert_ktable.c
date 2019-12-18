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
struct pfr_ktable {TYPE_1__* pfrkt_root; } ;
struct TYPE_2__ {int pfrkt_flags; int /*<<< orphan*/ * pfrkt_refcnt; } ;

/* Variables and functions */
 size_t PFR_REFCNT_ANCHOR ; 
 int PFR_TFLAG_REFDANCHOR ; 
 int /*<<< orphan*/  PF_RULES_WASSERT () ; 
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pfr_ktable*) ; 
 int /*<<< orphan*/  V_pfr_ktable_cnt ; 
 int /*<<< orphan*/  V_pfr_ktables ; 
 int /*<<< orphan*/  pfr_ktablehead ; 
 int /*<<< orphan*/  pfr_setflags_ktable (TYPE_1__*,int) ; 

__attribute__((used)) static void
pfr_insert_ktable(struct pfr_ktable *kt)
{

	PF_RULES_WASSERT();

	RB_INSERT(pfr_ktablehead, &V_pfr_ktables, kt);
	V_pfr_ktable_cnt++;
	if (kt->pfrkt_root != NULL)
		if (!kt->pfrkt_root->pfrkt_refcnt[PFR_REFCNT_ANCHOR]++)
			pfr_setflags_ktable(kt->pfrkt_root,
			    kt->pfrkt_root->pfrkt_flags|PFR_TFLAG_REFDANCHOR);
}