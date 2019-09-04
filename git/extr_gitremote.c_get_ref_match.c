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
struct refspec_item {char* dst; char* src; scalar_t__ matching; scalar_t__ pattern; scalar_t__ force; } ;
struct refspec {int nr; struct refspec_item* items; } ;
struct ref {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int FROM_SRC ; 
 int match_name_with_pattern (char const*,int /*<<< orphan*/ ,char const*,char**) ; 
 int /*<<< orphan*/  starts_with (int /*<<< orphan*/ ,char*) ; 
 char* xstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *get_ref_match(const struct refspec *rs, const struct ref *ref,
			   int send_mirror, int direction,
			   const struct refspec_item **ret_pat)
{
	const struct refspec_item *pat;
	char *name;
	int i;
	int matching_refs = -1;
	for (i = 0; i < rs->nr; i++) {
		const struct refspec_item *item = &rs->items[i];
		if (item->matching &&
		    (matching_refs == -1 || item->force)) {
			matching_refs = i;
			continue;
		}

		if (item->pattern) {
			const char *dst_side = item->dst ? item->dst : item->src;
			int match;
			if (direction == FROM_SRC)
				match = match_name_with_pattern(item->src, ref->name, dst_side, &name);
			else
				match = match_name_with_pattern(dst_side, ref->name, item->src, &name);
			if (match) {
				matching_refs = i;
				break;
			}
		}
	}
	if (matching_refs == -1)
		return NULL;

	pat = &rs->items[matching_refs];
	if (pat->matching) {
		/*
		 * "matching refs"; traditionally we pushed everything
		 * including refs outside refs/heads/ hierarchy, but
		 * that does not make much sense these days.
		 */
		if (!send_mirror && !starts_with(ref->name, "refs/heads/"))
			return NULL;
		name = xstrdup(ref->name);
	}
	if (ret_pat)
		*ret_pat = pat;
	return name;
}