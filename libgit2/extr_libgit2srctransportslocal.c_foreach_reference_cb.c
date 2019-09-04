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
typedef  int /*<<< orphan*/  git_revwalk ;
typedef  int /*<<< orphan*/  git_reference ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int GIT_ERROR_INVALID ; 
 scalar_t__ GIT_REFERENCE_DIRECT ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_target (int /*<<< orphan*/ *) ; 
 scalar_t__ git_reference_type (int /*<<< orphan*/ *) ; 
 int git_revwalk_hide (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int foreach_reference_cb(git_reference *reference, void *payload)
{
	git_revwalk *walk = (git_revwalk *)payload;
	int error;

	if (git_reference_type(reference) != GIT_REFERENCE_DIRECT) {
		git_reference_free(reference);
		return 0;
	}

	error = git_revwalk_hide(walk, git_reference_target(reference));
	/* The reference is in the local repository, so the target may not
	 * exist on the remote.  It also may not be a commit. */
	if (error == GIT_ENOTFOUND || error == GIT_ERROR_INVALID) {
		git_error_clear();
		error = 0;
	}

	git_reference_free(reference);

	return error;
}