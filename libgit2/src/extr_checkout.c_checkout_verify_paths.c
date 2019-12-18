#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_5__ {int /*<<< orphan*/  path; int /*<<< orphan*/  mode; } ;
struct TYPE_6__ {int /*<<< orphan*/  path; int /*<<< orphan*/  mode; } ;
struct TYPE_7__ {TYPE_1__ new_file; TYPE_2__ old_file; } ;
typedef  TYPE_3__ git_diff_delta ;

/* Variables and functions */
 int CHECKOUT_ACTION__REMOVE ; 
 int /*<<< orphan*/  GIT_ERROR_CHECKOUT ; 
 unsigned int GIT_PATH_REJECT_WORKDIR_DEFAULTS ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_isvalid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int checkout_verify_paths(
	git_repository *repo,
	int action,
	git_diff_delta *delta)
{
	unsigned int flags = GIT_PATH_REJECT_WORKDIR_DEFAULTS;

	if (action & CHECKOUT_ACTION__REMOVE) {
		if (!git_path_isvalid(repo, delta->old_file.path, delta->old_file.mode, flags)) {
			git_error_set(GIT_ERROR_CHECKOUT, "cannot remove invalid path '%s'", delta->old_file.path);
			return -1;
		}
	}

	if (action & ~CHECKOUT_ACTION__REMOVE) {
		if (!git_path_isvalid(repo, delta->new_file.path, delta->new_file.mode, flags)) {
			git_error_set(GIT_ERROR_CHECKOUT, "cannot checkout to invalid path '%s'", delta->new_file.path);
			return -1;
		}
	}

	return 0;
}