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
struct strbuf {char* buf; } ;
struct ref_filter {int /*<<< orphan*/ * name_patterns; scalar_t__ ignore_case; int /*<<< orphan*/  match_as_path; } ;
typedef  int /*<<< orphan*/  each_ref_fn ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  find_longest_prefix (struct strbuf*,int /*<<< orphan*/ ) ; 
 int for_each_fullref_in (char*,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static int for_each_fullref_in_pattern(struct ref_filter *filter,
				       each_ref_fn cb,
				       void *cb_data,
				       int broken)
{
	struct strbuf prefix = STRBUF_INIT;
	int ret;

	if (!filter->match_as_path) {
		/*
		 * in this case, the patterns are applied after
		 * prefixes like "refs/heads/" etc. are stripped off,
		 * so we have to look at everything:
		 */
		return for_each_fullref_in("", cb, cb_data, broken);
	}

	if (filter->ignore_case) {
		/*
		 * we can't handle case-insensitive comparisons,
		 * so just return everything and let the caller
		 * sort it out.
		 */
		return for_each_fullref_in("", cb, cb_data, broken);
	}

	if (!filter->name_patterns[0]) {
		/* no patterns; we have to look at everything */
		return for_each_fullref_in("", cb, cb_data, broken);
	}

	if (filter->name_patterns[1]) {
		/*
		 * multiple patterns; in theory this could still work as long
		 * as the patterns are disjoint. We'd just make multiple calls
		 * to for_each_ref(). But if they're not disjoint, we'd end up
		 * reporting the same ref multiple times. So let's punt on that
		 * for now.
		 */
		return for_each_fullref_in("", cb, cb_data, broken);
	}

	find_longest_prefix(&prefix, filter->name_patterns[0]);

	ret = for_each_fullref_in(prefix.buf, cb, cb_data, broken);
	strbuf_release(&prefix);
	return ret;
}