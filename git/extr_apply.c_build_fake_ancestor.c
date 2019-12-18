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
struct patch {char* old_name; char* new_name; scalar_t__ is_new; int /*<<< orphan*/  old_mode; int /*<<< orphan*/  lines_deleted; int /*<<< orphan*/  lines_added; int /*<<< orphan*/  old_oid_prefix; struct patch* next; } ;
struct object_id {int dummy; } ;
struct lock_file {int dummy; } ;
struct index_state {int /*<<< orphan*/ * member_0; } ;
struct cache_entry {int dummy; } ;
struct apply_state {char const* fake_ancestor; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_CACHE_OK_TO_ADD ; 
 int /*<<< orphan*/  COMMIT_LOCK ; 
 int /*<<< orphan*/  LOCK_DIE_ON_ERROR ; 
 struct lock_file LOCK_INIT ; 
 scalar_t__ S_ISGITLINK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ add_index_entry (struct index_state*,struct cache_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  discard_cache_entry (struct cache_entry*) ; 
 int /*<<< orphan*/  discard_index (struct index_state*) ; 
 int error (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ get_current_oid (struct apply_state*,char*,struct object_id*) ; 
 int /*<<< orphan*/  get_oid_blob (int /*<<< orphan*/ ,struct object_id*) ; 
 int /*<<< orphan*/  hold_lock_file_for_update (struct lock_file*,char const*,int /*<<< orphan*/ ) ; 
 struct cache_entry* make_cache_entry (struct index_state*,int /*<<< orphan*/ ,struct object_id*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preimage_oid_in_gitlink_patch (struct patch*,struct object_id*) ; 
 int write_locked_index (struct index_state*,struct lock_file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int build_fake_ancestor(struct apply_state *state, struct patch *list)
{
	struct patch *patch;
	struct index_state result = { NULL };
	struct lock_file lock = LOCK_INIT;
	int res;

	/* Once we start supporting the reverse patch, it may be
	 * worth showing the new sha1 prefix, but until then...
	 */
	for (patch = list; patch; patch = patch->next) {
		struct object_id oid;
		struct cache_entry *ce;
		const char *name;

		name = patch->old_name ? patch->old_name : patch->new_name;
		if (0 < patch->is_new)
			continue;

		if (S_ISGITLINK(patch->old_mode)) {
			if (!preimage_oid_in_gitlink_patch(patch, &oid))
				; /* ok, the textual part looks sane */
			else
				return error(_("sha1 information is lacking or "
					       "useless for submodule %s"), name);
		} else if (!get_oid_blob(patch->old_oid_prefix, &oid)) {
			; /* ok */
		} else if (!patch->lines_added && !patch->lines_deleted) {
			/* mode-only change: update the current */
			if (get_current_oid(state, patch->old_name, &oid))
				return error(_("mode change for %s, which is not "
					       "in current HEAD"), name);
		} else
			return error(_("sha1 information is lacking or useless "
				       "(%s)."), name);

		ce = make_cache_entry(&result, patch->old_mode, &oid, name, 0, 0);
		if (!ce)
			return error(_("make_cache_entry failed for path '%s'"),
				     name);
		if (add_index_entry(&result, ce, ADD_CACHE_OK_TO_ADD)) {
			discard_cache_entry(ce);
			return error(_("could not add %s to temporary index"),
				     name);
		}
	}

	hold_lock_file_for_update(&lock, state->fake_ancestor, LOCK_DIE_ON_ERROR);
	res = write_locked_index(&result, &lock, COMMIT_LOCK);
	discard_index(&result);

	if (res)
		return error(_("could not write temporary index to %s"),
			     state->fake_ancestor);

	return 0;
}