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
struct patch {int /*<<< orphan*/  old_name; int /*<<< orphan*/  old_mode; } ;
struct apply_state {int /*<<< orphan*/  cached; TYPE_1__* repo; int /*<<< orphan*/  ita_only; scalar_t__ update_index; } ;
struct TYPE_2__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ remove_file_from_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_or_warn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_path (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int remove_file(struct apply_state *state, struct patch *patch, int rmdir_empty)
{
	if (state->update_index && !state->ita_only) {
		if (remove_file_from_index(state->repo->index, patch->old_name) < 0)
			return error(_("unable to remove %s from index"), patch->old_name);
	}
	if (!state->cached) {
		if (!remove_or_warn(patch->old_mode, patch->old_name) && rmdir_empty) {
			remove_path(patch->old_name);
		}
	}
	return 0;
}