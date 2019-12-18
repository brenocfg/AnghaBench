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
typedef  int /*<<< orphan*/  git_merge_driver ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int GIT_EEXISTS ; 
 int /*<<< orphan*/  GIT_ERROR_MERGE ; 
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ git_rwlock_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_rwlock_wrunlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ merge_driver_registry ; 
 int /*<<< orphan*/  merge_driver_registry_find (int /*<<< orphan*/ *,char const*) ; 
 int merge_driver_registry_insert (char const*,int /*<<< orphan*/ *) ; 

int git_merge_driver_register(const char *name, git_merge_driver *driver)
{
	int error;

	assert(name && driver);

	if (git_rwlock_wrlock(&merge_driver_registry.lock) < 0) {
		git_error_set(GIT_ERROR_OS, "failed to lock merge driver registry");
		return -1;
	}

	if (!merge_driver_registry_find(NULL, name)) {
		git_error_set(GIT_ERROR_MERGE, "attempt to reregister existing driver '%s'",
			name);
		error = GIT_EEXISTS;
		goto done;
	}

	error = merge_driver_registry_insert(name, driver);

done:
	git_rwlock_wrunlock(&merge_driver_registry.lock);
	return error;
}