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
struct stat {int st_mode; } ;
typedef  int mode_t ;
struct TYPE_4__ {int /*<<< orphan*/  stat_calls; } ;
struct TYPE_5__ {TYPE_1__ perfdata; } ;
typedef  TYPE_2__ checkout_data ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 scalar_t__ ENOTDIR ; 
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ p_lstat (char const*,struct stat*) ; 

__attribute__((used)) static int checkout_safe_for_update_only(
	checkout_data *data, const char *path, mode_t expected_mode)
{
	struct stat st;

	data->perfdata.stat_calls++;

	if (p_lstat(path, &st) < 0) {
		/* if doesn't exist, then no error and no update */
		if (errno == ENOENT || errno == ENOTDIR)
			return 0;

		/* otherwise, stat error and no update */
		git_error_set(GIT_ERROR_OS, "failed to stat '%s'", path);
		return -1;
	}

	/* only safe for update if this is the same type of file */
	if ((st.st_mode & ~0777) == (expected_mode & ~0777))
		return 1;

	return 0;
}