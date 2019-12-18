#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct object_id {int dummy; } ;
struct object_array {int nr; TYPE_3__* objects; } ;
struct merge_options {int /*<<< orphan*/  repo; TYPE_1__* priv; } ;
struct commit {int dummy; } ;
struct TYPE_6__ {TYPE_2__* item; } ;
struct TYPE_5__ {int /*<<< orphan*/  oid; } ;
struct TYPE_4__ {int /*<<< orphan*/  call_depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ add_submodule_odb (char const*) ; 
 int find_first_merges (int /*<<< orphan*/ ,struct object_array*,char const*,struct commit*,struct commit*) ; 
 scalar_t__ in_merge_bases (struct commit*,struct commit*) ; 
 scalar_t__ is_null_oid (struct object_id const*) ; 
 struct commit* lookup_commit_reference (int /*<<< orphan*/ ,struct object_id const*) ; 
 int /*<<< orphan*/  object_array_clear (struct object_array*) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidcpy (struct object_id*,struct object_id const*) ; 
 int /*<<< orphan*/  output (struct merge_options*,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  output_commit_title (struct merge_options*,struct commit*) ; 
 int /*<<< orphan*/  print_commit (struct commit*) ; 
 scalar_t__ show (struct merge_options*,int) ; 

__attribute__((used)) static int merge_submodule(struct merge_options *opt,
			   struct object_id *result, const char *path,
			   const struct object_id *base, const struct object_id *a,
			   const struct object_id *b)
{
	struct commit *commit_base, *commit_a, *commit_b;
	int parent_count;
	struct object_array merges;

	int i;
	int search = !opt->priv->call_depth;

	/* store a in result in case we fail */
	oidcpy(result, a);

	/* we can not handle deletion conflicts */
	if (is_null_oid(base))
		return 0;
	if (is_null_oid(a))
		return 0;
	if (is_null_oid(b))
		return 0;

	if (add_submodule_odb(path)) {
		output(opt, 1, _("Failed to merge submodule %s (not checked out)"), path);
		return 0;
	}

	if (!(commit_base = lookup_commit_reference(opt->repo, base)) ||
	    !(commit_a = lookup_commit_reference(opt->repo, a)) ||
	    !(commit_b = lookup_commit_reference(opt->repo, b))) {
		output(opt, 1, _("Failed to merge submodule %s (commits not present)"), path);
		return 0;
	}

	/* check whether both changes are forward */
	if (!in_merge_bases(commit_base, commit_a) ||
	    !in_merge_bases(commit_base, commit_b)) {
		output(opt, 1, _("Failed to merge submodule %s (commits don't follow merge-base)"), path);
		return 0;
	}

	/* Case #1: a is contained in b or vice versa */
	if (in_merge_bases(commit_a, commit_b)) {
		oidcpy(result, b);
		if (show(opt, 3)) {
			output(opt, 3, _("Fast-forwarding submodule %s to the following commit:"), path);
			output_commit_title(opt, commit_b);
		} else if (show(opt, 2))
			output(opt, 2, _("Fast-forwarding submodule %s"), path);
		else
			; /* no output */

		return 1;
	}
	if (in_merge_bases(commit_b, commit_a)) {
		oidcpy(result, a);
		if (show(opt, 3)) {
			output(opt, 3, _("Fast-forwarding submodule %s to the following commit:"), path);
			output_commit_title(opt, commit_a);
		} else if (show(opt, 2))
			output(opt, 2, _("Fast-forwarding submodule %s"), path);
		else
			; /* no output */

		return 1;
	}

	/*
	 * Case #2: There are one or more merges that contain a and b in
	 * the submodule. If there is only one, then present it as a
	 * suggestion to the user, but leave it marked unmerged so the
	 * user needs to confirm the resolution.
	 */

	/* Skip the search if makes no sense to the calling context.  */
	if (!search)
		return 0;

	/* find commit which merges them */
	parent_count = find_first_merges(opt->repo, &merges, path,
					 commit_a, commit_b);
	switch (parent_count) {
	case 0:
		output(opt, 1, _("Failed to merge submodule %s (merge following commits not found)"), path);
		break;

	case 1:
		output(opt, 1, _("Failed to merge submodule %s (not fast-forward)"), path);
		output(opt, 2, _("Found a possible merge resolution for the submodule:\n"));
		print_commit((struct commit *) merges.objects[0].item);
		output(opt, 2, _(
		       "If this is correct simply add it to the index "
		       "for example\n"
		       "by using:\n\n"
		       "  git update-index --cacheinfo 160000 %s \"%s\"\n\n"
		       "which will accept this suggestion.\n"),
		       oid_to_hex(&merges.objects[0].item->oid), path);
		break;

	default:
		output(opt, 1, _("Failed to merge submodule %s (multiple merges found)"), path);
		for (i = 0; i < merges.nr; i++)
			print_commit((struct commit *) merges.objects[i].item);
	}

	object_array_clear(&merges);
	return 0;
}