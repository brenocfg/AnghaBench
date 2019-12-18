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
struct patch {scalar_t__ new_name; int /*<<< orphan*/  new_mode; scalar_t__ old_name; scalar_t__ is_delete; scalar_t__ is_rename; int /*<<< orphan*/  old_mode; struct patch* next; } ;
struct apply_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPLY_SYMLINK_GOES_AWAY ; 
 int /*<<< orphan*/  APPLY_SYMLINK_IN_RESULT ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_symlink_changes (struct apply_state*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void prepare_symlink_changes(struct apply_state *state, struct patch *patch)
{
	for ( ; patch; patch = patch->next) {
		if ((patch->old_name && S_ISLNK(patch->old_mode)) &&
		    (patch->is_rename || patch->is_delete))
			/* the symlink at patch->old_name is removed */
			register_symlink_changes(state, patch->old_name, APPLY_SYMLINK_GOES_AWAY);

		if (patch->new_name && S_ISLNK(patch->new_mode))
			/* the symlink at patch->new_name is created or remains */
			register_symlink_changes(state, patch->new_name, APPLY_SYMLINK_IN_RESULT);
	}
}