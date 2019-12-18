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
typedef  int /*<<< orphan*/  git_config_entries ;
struct TYPE_3__ {int /*<<< orphan*/  values_mutex; int /*<<< orphan*/ * entries; } ;
typedef  TYPE_1__ config_file_backend ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int /*<<< orphan*/  git_config_entries_incref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int git_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int config_file_entries_take(git_config_entries **out, config_file_backend *b)
{
	int error;

	if ((error = git_mutex_lock(&b->values_mutex)) < 0) {
		git_error_set(GIT_ERROR_OS, "failed to lock config backend");
		return error;
	}

	git_config_entries_incref(b->entries);
	*out = b->entries;

	git_mutex_unlock(&b->values_mutex);

	return 0;
}