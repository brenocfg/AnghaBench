#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  inuse_cnt; } ;
typedef  TYPE_1__ git_mwindow ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_THREAD ; 
 int /*<<< orphan*/  git__mwindow_mutex ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ git_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_mutex_unlock (int /*<<< orphan*/ *) ; 

void git_mwindow_close(git_mwindow **window)
{
	git_mwindow *w = *window;
	if (w) {
		if (git_mutex_lock(&git__mwindow_mutex)) {
			git_error_set(GIT_ERROR_THREAD, "unable to lock mwindow mutex");
			return;
		}

		w->inuse_cnt--;
		git_mutex_unlock(&git__mwindow_mutex);
		*window = NULL;
	}
}