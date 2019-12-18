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
typedef  int /*<<< orphan*/  git_filter ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int GIT_EEXISTS ; 
 int /*<<< orphan*/  GIT_ERROR_FILTER ; 
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__ filter_registry ; 
 int /*<<< orphan*/  filter_registry_find (int /*<<< orphan*/ *,char const*) ; 
 int filter_registry_insert (char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ git_rwlock_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_rwlock_wrunlock (int /*<<< orphan*/ *) ; 

int git_filter_register(
	const char *name, git_filter *filter, int priority)
{
	int error;

	assert(name && filter);

	if (git_rwlock_wrlock(&filter_registry.lock) < 0) {
		git_error_set(GIT_ERROR_OS, "failed to lock filter registry");
		return -1;
	}

	if (!filter_registry_find(NULL, name)) {
		git_error_set(
			GIT_ERROR_FILTER, "attempt to reregister existing filter '%s'", name);
		error = GIT_EEXISTS;
		goto done;
	}

	error = filter_registry_insert(name, filter, priority);

done:
	git_rwlock_wrunlock(&filter_registry.lock);
	return error;
}