#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ show; int flags; } ;
typedef  TYPE_1__ git_status_options ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_VERSION (TYPE_1__ const*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  GIT_STATUS_OPTIONS_VERSION ; 
 int GIT_STATUS_OPT_NO_REFRESH ; 
 int GIT_STATUS_OPT_UPDATE_INDEX ; 
 scalar_t__ GIT_STATUS_SHOW_WORKDIR_ONLY ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int status_validate_options(const git_status_options *opts)
{
	if (!opts)
		return 0;

	GIT_ERROR_CHECK_VERSION(opts, GIT_STATUS_OPTIONS_VERSION, "git_status_options");

	if (opts->show > GIT_STATUS_SHOW_WORKDIR_ONLY) {
		git_error_set(GIT_ERROR_INVALID, "unknown status 'show' option");
		return -1;
	}

	if ((opts->flags & GIT_STATUS_OPT_NO_REFRESH) != 0 &&
		(opts->flags & GIT_STATUS_OPT_UPDATE_INDEX) != 0) {
		git_error_set(GIT_ERROR_INVALID, "updating index from status "
			"is not allowed when index refresh is disabled");
		return -1;
	}

	return 0;
}