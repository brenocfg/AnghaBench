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
struct moved_entry {int /*<<< orphan*/  ent; struct moved_entry* next_line; } ;
struct moved_block {struct moved_entry* match; } ;
struct hashmap {int /*<<< orphan*/  (* cmpfn ) (struct diff_options*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct diff_options {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct diff_options*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pmb_advance_or_null(struct diff_options *o,
				struct moved_entry *match,
				struct hashmap *hm,
				struct moved_block *pmb,
				int pmb_nr)
{
	int i;
	for (i = 0; i < pmb_nr; i++) {
		struct moved_entry *prev = pmb[i].match;
		struct moved_entry *cur = (prev && prev->next_line) ?
				prev->next_line : NULL;
		if (cur && !hm->cmpfn(o, &cur->ent, &match->ent, NULL)) {
			pmb[i].match = cur;
		} else {
			pmb[i].match = NULL;
		}
	}
}