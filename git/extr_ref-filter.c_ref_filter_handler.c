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
struct ref_filter_cbdata {int /*<<< orphan*/  array; int /*<<< orphan*/  no_contains_cache; int /*<<< orphan*/  contains_cache; struct ref_filter* filter; } ;
struct TYPE_2__ {scalar_t__ nr; } ;
struct ref_filter {unsigned int kind; scalar_t__ no_commit; scalar_t__ with_commit; scalar_t__ verbose; scalar_t__ merge_commit; TYPE_1__ points_at; } ;
struct ref_array_item {int flag; unsigned int kind; struct commit* commit; } ;
struct object_id {int dummy; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int REF_BAD_NAME ; 
 int REF_ISBROKEN ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ commit_contains (struct ref_filter*,struct commit*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  filter_pattern_match (struct ref_filter*,char const*) ; 
 unsigned int filter_ref_kind (struct ref_filter*,char const*) ; 
 struct commit* lookup_commit_reference_gently (int /*<<< orphan*/ ,struct object_id const*,int) ; 
 int /*<<< orphan*/  match_points_at (TYPE_1__*,struct object_id const*,char const*) ; 
 struct ref_array_item* ref_array_push (int /*<<< orphan*/ ,char const*,struct object_id const*) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int ref_filter_handler(const char *refname, const struct object_id *oid, int flag, void *cb_data)
{
	struct ref_filter_cbdata *ref_cbdata = cb_data;
	struct ref_filter *filter = ref_cbdata->filter;
	struct ref_array_item *ref;
	struct commit *commit = NULL;
	unsigned int kind;

	if (flag & REF_BAD_NAME) {
		warning(_("ignoring ref with broken name %s"), refname);
		return 0;
	}

	if (flag & REF_ISBROKEN) {
		warning(_("ignoring broken ref %s"), refname);
		return 0;
	}

	/* Obtain the current ref kind from filter_ref_kind() and ignore unwanted refs. */
	kind = filter_ref_kind(filter, refname);
	if (!(kind & filter->kind))
		return 0;

	if (!filter_pattern_match(filter, refname))
		return 0;

	if (filter->points_at.nr && !match_points_at(&filter->points_at, oid, refname))
		return 0;

	/*
	 * A merge filter is applied on refs pointing to commits. Hence
	 * obtain the commit using the 'oid' available and discard all
	 * non-commits early. The actual filtering is done later.
	 */
	if (filter->merge_commit || filter->with_commit || filter->no_commit || filter->verbose) {
		commit = lookup_commit_reference_gently(the_repository, oid,
							1);
		if (!commit)
			return 0;
		/* We perform the filtering for the '--contains' option... */
		if (filter->with_commit &&
		    !commit_contains(filter, commit, filter->with_commit, &ref_cbdata->contains_cache))
			return 0;
		/* ...or for the `--no-contains' option */
		if (filter->no_commit &&
		    commit_contains(filter, commit, filter->no_commit, &ref_cbdata->no_contains_cache))
			return 0;
	}

	/*
	 * We do not open the object yet; sort may only need refname
	 * to do its job and the resulting list may yet to be pruned
	 * by maxcount logic.
	 */
	ref = ref_array_push(ref_cbdata->array, refname, oid);
	ref->commit = commit;
	ref->flag = flag;
	ref->kind = kind;

	return 0;
}