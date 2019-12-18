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
struct pfr_table {scalar_t__* pfrt_anchor; } ;
struct pf_ruleset {int tables; } ;
struct TYPE_2__ {int tables; } ;

/* Variables and functions */
 int PFR_FLAG_ALLRSETS ; 
 int /*<<< orphan*/  PF_RULES_ASSERT () ; 
 int V_pfr_ktable_cnt ; 
 struct pf_ruleset* pf_find_ruleset (scalar_t__*) ; 
 TYPE_1__ pf_main_ruleset ; 

int
pfr_table_count(struct pfr_table *filter, int flags)
{
	struct pf_ruleset *rs;

	PF_RULES_ASSERT();

	if (flags & PFR_FLAG_ALLRSETS)
		return (V_pfr_ktable_cnt);
	if (filter->pfrt_anchor[0]) {
		rs = pf_find_ruleset(filter->pfrt_anchor);
		return ((rs != NULL) ? rs->tables : -1);
	}
	return (pf_main_ruleset.tables);
}