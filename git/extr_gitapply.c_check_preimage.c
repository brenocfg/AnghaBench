#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
struct patch {char* old_name; int is_new; unsigned int new_mode; unsigned int old_mode; scalar_t__ is_delete; } ;
struct cache_entry {unsigned int ce_mode; } ;
struct apply_state {scalar_t__ cached; TYPE_1__* repo; scalar_t__ check_index; } ;
struct TYPE_5__ {struct cache_entry** cache; } ;
struct TYPE_4__ {TYPE_2__* index; } ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  FREE_AND_NULL (char*) ; 
 unsigned int S_IFMT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 unsigned int ce_mode_from_stat (struct cache_entry*,int /*<<< orphan*/ ) ; 
 scalar_t__ checkout_target (TYPE_2__*,struct cache_entry*,struct stat*) ; 
 scalar_t__ errno ; 
 int error (int /*<<< orphan*/ ,char const*) ; 
 int error_errno (char*,char const*) ; 
 int index_name_pos (TYPE_2__*,char const*,int /*<<< orphan*/ ) ; 
 int lstat (char const*,struct stat*) ; 
 struct patch* previous_patch (struct apply_state*,struct patch*,int*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ verify_index_match (struct apply_state*,struct cache_entry*,struct stat*) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char const*,unsigned int,unsigned int) ; 

__attribute__((used)) static int check_preimage(struct apply_state *state,
			  struct patch *patch,
			  struct cache_entry **ce,
			  struct stat *st)
{
	const char *old_name = patch->old_name;
	struct patch *previous = NULL;
	int stat_ret = 0, status;
	unsigned st_mode = 0;

	if (!old_name)
		return 0;

	assert(patch->is_new <= 0);
	previous = previous_patch(state, patch, &status);

	if (status)
		return error(_("path %s has been renamed/deleted"), old_name);
	if (previous) {
		st_mode = previous->new_mode;
	} else if (!state->cached) {
		stat_ret = lstat(old_name, st);
		if (stat_ret && errno != ENOENT)
			return error_errno("%s", old_name);
	}

	if (state->check_index && !previous) {
		int pos = index_name_pos(state->repo->index, old_name,
					 strlen(old_name));
		if (pos < 0) {
			if (patch->is_new < 0)
				goto is_new;
			return error(_("%s: does not exist in index"), old_name);
		}
		*ce = state->repo->index->cache[pos];
		if (stat_ret < 0) {
			if (checkout_target(state->repo->index, *ce, st))
				return -1;
		}
		if (!state->cached && verify_index_match(state, *ce, st))
			return error(_("%s: does not match index"), old_name);
		if (state->cached)
			st_mode = (*ce)->ce_mode;
	} else if (stat_ret < 0) {
		if (patch->is_new < 0)
			goto is_new;
		return error_errno("%s", old_name);
	}

	if (!state->cached && !previous)
		st_mode = ce_mode_from_stat(*ce, st->st_mode);

	if (patch->is_new < 0)
		patch->is_new = 0;
	if (!patch->old_mode)
		patch->old_mode = st_mode;
	if ((st_mode ^ patch->old_mode) & S_IFMT)
		return error(_("%s: wrong type"), old_name);
	if (st_mode != patch->old_mode)
		warning(_("%s has type %o, expected %o"),
			old_name, st_mode, patch->old_mode);
	if (!patch->new_mode && !patch->is_delete)
		patch->new_mode = st_mode;
	return 0;

 is_new:
	patch->is_new = 1;
	patch->is_delete = 0;
	FREE_AND_NULL(patch->old_name);
	return 0;
}