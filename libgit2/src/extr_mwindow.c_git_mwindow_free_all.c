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
typedef  int /*<<< orphan*/  git_mwindow_file ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_THREAD ; 
 int /*<<< orphan*/  git__mwindow_mutex ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ git_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_mwindow_free_all_locked (int /*<<< orphan*/ *) ; 

void git_mwindow_free_all(git_mwindow_file *mwf)
{
	if (git_mutex_lock(&git__mwindow_mutex)) {
		git_error_set(GIT_ERROR_THREAD, "unable to lock mwindow mutex");
		return;
	}

	git_mwindow_free_all_locked(mwf);

	git_mutex_unlock(&git__mwindow_mutex);
}