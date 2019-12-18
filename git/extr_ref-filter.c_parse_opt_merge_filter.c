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
struct ref_filter {int /*<<< orphan*/  merge_commit; scalar_t__ merge; } ;
struct option {int /*<<< orphan*/  long_name; struct ref_filter* value; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON_OPT_NEG (int) ; 
 scalar_t__ REF_FILTER_MERGED_INCLUDE ; 
 scalar_t__ REF_FILTER_MERGED_OMIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 int error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_oid (char const*,struct object_id*) ; 
 int /*<<< orphan*/  lookup_commit_reference_gently (int /*<<< orphan*/ ,struct object_id*,int /*<<< orphan*/ ) ; 
 int starts_with (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  the_repository ; 

int parse_opt_merge_filter(const struct option *opt, const char *arg, int unset)
{
	struct ref_filter *rf = opt->value;
	struct object_id oid;
	int no_merged = starts_with(opt->long_name, "no");

	BUG_ON_OPT_NEG(unset);

	if (rf->merge) {
		if (no_merged) {
			return error(_("option `%s' is incompatible with --merged"),
				     opt->long_name);
		} else {
			return error(_("option `%s' is incompatible with --no-merged"),
				     opt->long_name);
		}
	}

	rf->merge = no_merged
		? REF_FILTER_MERGED_OMIT
		: REF_FILTER_MERGED_INCLUDE;

	if (get_oid(arg, &oid))
		die(_("malformed object name %s"), arg);

	rf->merge_commit = lookup_commit_reference_gently(the_repository,
							  &oid, 0);
	if (!rf->merge_commit)
		return error(_("option `%s' must point to a commit"), opt->long_name);

	return 0;
}