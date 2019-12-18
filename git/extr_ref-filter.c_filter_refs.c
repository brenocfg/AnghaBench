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
struct ref_filter_cbdata {int /*<<< orphan*/  no_contains_cache; int /*<<< orphan*/  contains_cache; struct ref_filter* filter; struct ref_array* array; } ;
struct ref_filter {unsigned int kind; scalar_t__ merge_commit; } ;
struct ref_array {int dummy; } ;

/* Variables and functions */
 int FILTER_REFS_ALL ; 
 unsigned int FILTER_REFS_BRANCHES ; 
 int FILTER_REFS_DETACHED_HEAD ; 
 unsigned int FILTER_REFS_INCLUDE_BROKEN ; 
 unsigned int FILTER_REFS_KIND_MASK ; 
 unsigned int FILTER_REFS_REMOTES ; 
 unsigned int FILTER_REFS_TAGS ; 
 int /*<<< orphan*/  clear_contains_cache (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  do_merge_filter (struct ref_filter_cbdata*) ; 
 int for_each_fullref_in (char*,int /*<<< orphan*/ ,struct ref_filter_cbdata*,unsigned int) ; 
 int for_each_fullref_in_pattern (struct ref_filter*,int /*<<< orphan*/ ,struct ref_filter_cbdata*,unsigned int) ; 
 int /*<<< orphan*/  head_ref (int /*<<< orphan*/ ,struct ref_filter_cbdata*) ; 
 int /*<<< orphan*/  init_contains_cache (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ref_filter_handler ; 

int filter_refs(struct ref_array *array, struct ref_filter *filter, unsigned int type)
{
	struct ref_filter_cbdata ref_cbdata;
	int ret = 0;
	unsigned int broken = 0;

	ref_cbdata.array = array;
	ref_cbdata.filter = filter;

	if (type & FILTER_REFS_INCLUDE_BROKEN)
		broken = 1;
	filter->kind = type & FILTER_REFS_KIND_MASK;

	init_contains_cache(&ref_cbdata.contains_cache);
	init_contains_cache(&ref_cbdata.no_contains_cache);

	/*  Simple per-ref filtering */
	if (!filter->kind)
		die("filter_refs: invalid type");
	else {
		/*
		 * For common cases where we need only branches or remotes or tags,
		 * we only iterate through those refs. If a mix of refs is needed,
		 * we iterate over all refs and filter out required refs with the help
		 * of filter_ref_kind().
		 */
		if (filter->kind == FILTER_REFS_BRANCHES)
			ret = for_each_fullref_in("refs/heads/", ref_filter_handler, &ref_cbdata, broken);
		else if (filter->kind == FILTER_REFS_REMOTES)
			ret = for_each_fullref_in("refs/remotes/", ref_filter_handler, &ref_cbdata, broken);
		else if (filter->kind == FILTER_REFS_TAGS)
			ret = for_each_fullref_in("refs/tags/", ref_filter_handler, &ref_cbdata, broken);
		else if (filter->kind & FILTER_REFS_ALL)
			ret = for_each_fullref_in_pattern(filter, ref_filter_handler, &ref_cbdata, broken);
		if (!ret && (filter->kind & FILTER_REFS_DETACHED_HEAD))
			head_ref(ref_filter_handler, &ref_cbdata);
	}

	clear_contains_cache(&ref_cbdata.contains_cache);
	clear_contains_cache(&ref_cbdata.no_contains_cache);

	/*  Filters that need revision walking */
	if (filter->merge_commit)
		do_merge_filter(&ref_cbdata);

	return ret;
}