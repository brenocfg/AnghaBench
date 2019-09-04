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
struct moved_entry {struct moved_entry* next_line; } ;
struct moved_block {struct moved_entry* match; } ;
struct hashmap {int dummy; } ;
struct diff_options {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmp_in_block_with_wsd (struct diff_options*,struct moved_entry*,struct moved_entry*,struct moved_block*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct moved_entry* hashmap_get_next (struct hashmap*,struct moved_entry*) ; 
 int /*<<< orphan*/  moved_block_clear (struct moved_block*) ; 
 char* xcalloc (int,int) ; 

__attribute__((used)) static void pmb_advance_or_null_multi_match(struct diff_options *o,
					    struct moved_entry *match,
					    struct hashmap *hm,
					    struct moved_block *pmb,
					    int pmb_nr, int n)
{
	int i;
	char *got_match = xcalloc(1, pmb_nr);

	for (; match; match = hashmap_get_next(hm, match)) {
		for (i = 0; i < pmb_nr; i++) {
			struct moved_entry *prev = pmb[i].match;
			struct moved_entry *cur = (prev && prev->next_line) ?
					prev->next_line : NULL;
			if (!cur)
				continue;
			if (!cmp_in_block_with_wsd(o, cur, match, &pmb[i], n))
				got_match[i] |= 1;
		}
	}

	for (i = 0; i < pmb_nr; i++) {
		if (got_match[i]) {
			/* Advance to the next line */
			pmb[i].match = pmb[i].match->next_line;
		} else {
			moved_block_clear(&pmb[i]);
		}
	}

	free(got_match);
}