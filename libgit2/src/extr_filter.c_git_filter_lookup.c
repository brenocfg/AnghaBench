#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * filter; int /*<<< orphan*/  initialized; } ;
typedef  TYPE_1__ git_filter_def ;
typedef  int /*<<< orphan*/  git_filter ;
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 scalar_t__ filter_initialize (TYPE_1__*) ; 
 TYPE_3__ filter_registry ; 
 TYPE_1__* filter_registry_lookup (size_t*,char const*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ git_rwlock_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_rwlock_rdunlock (int /*<<< orphan*/ *) ; 

git_filter *git_filter_lookup(const char *name)
{
	size_t pos;
	git_filter_def *fdef;
	git_filter *filter = NULL;

	if (git_rwlock_rdlock(&filter_registry.lock) < 0) {
		git_error_set(GIT_ERROR_OS, "failed to lock filter registry");
		return NULL;
	}

	if ((fdef = filter_registry_lookup(&pos, name)) == NULL ||
		(!fdef->initialized && filter_initialize(fdef) < 0))
		goto done;

	filter = fdef->filter;

done:
	git_rwlock_rdunlock(&filter_registry.lock);
	return filter;
}