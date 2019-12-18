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
typedef  scalar_t__ uint32_t ;
struct tp_entry {scalar_t__ sysindex; } ;
struct tp_entries {int dummy; } ;

/* Variables and functions */
 struct tp_entry* TAILQ_FIRST (struct tp_entries*) ; 
 struct tp_entry* TAILQ_LAST (struct tp_entries*,int /*<<< orphan*/ ) ; 
 struct tp_entry* TAILQ_NEXT (struct tp_entry*,int /*<<< orphan*/ ) ; 
 struct tp_entry* TAILQ_PREV (struct tp_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bridge_compare_sysidx (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tp_e ; 
 int /*<<< orphan*/  tp_entries ; 

__attribute__((used)) static struct tp_entry *
bridge_addrs_find_pos(struct tp_entries *headp, uint32_t b_idx)
{
	uint32_t t_idx;
	struct tp_entry *t1;

	if ((t1 = TAILQ_FIRST(headp)) == NULL ||
	    bridge_compare_sysidx(b_idx, t1->sysindex) < 0)
		return (NULL);

	t_idx = t1->sysindex;

	for (t1 = TAILQ_NEXT(t1, tp_e); t1 != NULL; t1 = TAILQ_NEXT(t1, tp_e)) {

		if (t1->sysindex != t_idx) {
			if (bridge_compare_sysidx(b_idx, t1->sysindex) < 0)
				return (TAILQ_PREV(t1, tp_entries, tp_e));
			else
				t_idx = t1->sysindex;
		}
	}

	if (t1 == NULL)
		t1 = TAILQ_LAST(headp, tp_entries);

	return (t1);
}