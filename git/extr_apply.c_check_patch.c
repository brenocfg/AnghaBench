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
struct stat {int dummy; } ;
struct patch {char* old_name; char* new_name; int rejected; scalar_t__ is_new; int direct_to_threeway; int new_mode; int old_mode; int /*<<< orphan*/  is_delete; scalar_t__ is_copy; scalar_t__ is_rename; } ;
struct cache_entry {int dummy; } ;
struct apply_state {int /*<<< orphan*/  unsafe_paths; scalar_t__ threeway; } ;

/* Variables and functions */
#define  EXISTS_IN_INDEX 129 
#define  EXISTS_IN_WORKTREE 128 
 int S_IFMT ; 
 int S_IFREG ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apply_data (struct apply_state*,struct patch*,struct stat*,struct cache_entry*) ; 
 int check_preimage (struct apply_state*,struct patch*,struct cache_entry**,struct stat*) ; 
 int check_to_create (struct apply_state*,char const*,int) ; 
 scalar_t__ check_unsafe_path (struct patch*) ; 
 int error (int /*<<< orphan*/ ,...) ; 
 struct patch* in_fn_table (struct apply_state*,char const*) ; 
 scalar_t__ path_is_beyond_symlink (struct apply_state*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 scalar_t__ to_be_deleted (struct patch*) ; 
 scalar_t__ was_deleted (struct patch*) ; 

__attribute__((used)) static int check_patch(struct apply_state *state, struct patch *patch)
{
	struct stat st;
	const char *old_name = patch->old_name;
	const char *new_name = patch->new_name;
	const char *name = old_name ? old_name : new_name;
	struct cache_entry *ce = NULL;
	struct patch *tpatch;
	int ok_if_exists;
	int status;

	patch->rejected = 1; /* we will drop this after we succeed */

	status = check_preimage(state, patch, &ce, &st);
	if (status)
		return status;
	old_name = patch->old_name;

	/*
	 * A type-change diff is always split into a patch to delete
	 * old, immediately followed by a patch to create new (see
	 * diff.c::run_diff()); in such a case it is Ok that the entry
	 * to be deleted by the previous patch is still in the working
	 * tree and in the index.
	 *
	 * A patch to swap-rename between A and B would first rename A
	 * to B and then rename B to A.  While applying the first one,
	 * the presence of B should not stop A from getting renamed to
	 * B; ask to_be_deleted() about the later rename.  Removal of
	 * B and rename from A to B is handled the same way by asking
	 * was_deleted().
	 */
	if ((tpatch = in_fn_table(state, new_name)) &&
	    (was_deleted(tpatch) || to_be_deleted(tpatch)))
		ok_if_exists = 1;
	else
		ok_if_exists = 0;

	if (new_name &&
	    ((0 < patch->is_new) || patch->is_rename || patch->is_copy)) {
		int err = check_to_create(state, new_name, ok_if_exists);

		if (err && state->threeway) {
			patch->direct_to_threeway = 1;
		} else switch (err) {
		case 0:
			break; /* happy */
		case EXISTS_IN_INDEX:
			return error(_("%s: already exists in index"), new_name);
			break;
		case EXISTS_IN_WORKTREE:
			return error(_("%s: already exists in working directory"),
				     new_name);
		default:
			return err;
		}

		if (!patch->new_mode) {
			if (0 < patch->is_new)
				patch->new_mode = S_IFREG | 0644;
			else
				patch->new_mode = patch->old_mode;
		}
	}

	if (new_name && old_name) {
		int same = !strcmp(old_name, new_name);
		if (!patch->new_mode)
			patch->new_mode = patch->old_mode;
		if ((patch->old_mode ^ patch->new_mode) & S_IFMT) {
			if (same)
				return error(_("new mode (%o) of %s does not "
					       "match old mode (%o)"),
					patch->new_mode, new_name,
					patch->old_mode);
			else
				return error(_("new mode (%o) of %s does not "
					       "match old mode (%o) of %s"),
					patch->new_mode, new_name,
					patch->old_mode, old_name);
		}
	}

	if (!state->unsafe_paths && check_unsafe_path(patch))
		return -128;

	/*
	 * An attempt to read from or delete a path that is beyond a
	 * symbolic link will be prevented by load_patch_target() that
	 * is called at the beginning of apply_data() so we do not
	 * have to worry about a patch marked with "is_delete" bit
	 * here.  We however need to make sure that the patch result
	 * is not deposited to a path that is beyond a symbolic link
	 * here.
	 */
	if (!patch->is_delete && path_is_beyond_symlink(state, patch->new_name))
		return error(_("affected file '%s' is beyond a symbolic link"),
			     patch->new_name);

	if (apply_data(state, patch, &st, ce) < 0)
		return error(_("%s: patch does not apply"), name);
	patch->rejected = 0;
	return 0;
}