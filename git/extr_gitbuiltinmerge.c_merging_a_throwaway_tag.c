#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tag {int /*<<< orphan*/  tag; } ;
struct object_id {int dummy; } ;
struct commit {int dummy; } ;
struct TYPE_4__ {TYPE_1__* obj; } ;
struct TYPE_3__ {scalar_t__ type; int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 scalar_t__ OBJ_TAG ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_2__* merge_remote_util (struct commit*) ; 
 scalar_t__ oideq (struct object_id*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_ref (char*,struct object_id*) ; 
 char* xstrfmt (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int merging_a_throwaway_tag(struct commit *commit)
{
	char *tag_ref;
	struct object_id oid;
	int is_throwaway_tag = 0;

	/* Are we merging a tag? */
	if (!merge_remote_util(commit) ||
	    !merge_remote_util(commit)->obj ||
	    merge_remote_util(commit)->obj->type != OBJ_TAG)
		return is_throwaway_tag;

	/*
	 * Now we know we are merging a tag object.  Are we downstream
	 * and following the tags from upstream?  If so, we must have
	 * the tag object pointed at by "refs/tags/$T" where $T is the
	 * tagname recorded in the tag object.  We want to allow such
	 * a "just to catch up" merge to fast-forward.
	 *
	 * Otherwise, we are playing an integrator's role, making a
	 * merge with a throw-away tag from a contributor with
	 * something like "git pull $contributor $signed_tag".
	 * We want to forbid such a merge from fast-forwarding
	 * by default; otherwise we would not keep the signature
	 * anywhere.
	 */
	tag_ref = xstrfmt("refs/tags/%s",
			  ((struct tag *)merge_remote_util(commit)->obj)->tag);
	if (!read_ref(tag_ref, &oid) &&
	    oideq(&oid, &merge_remote_util(commit)->obj->oid))
		is_throwaway_tag = 0;
	else
		is_throwaway_tag = 1;
	free(tag_ref);
	return is_throwaway_tag;
}