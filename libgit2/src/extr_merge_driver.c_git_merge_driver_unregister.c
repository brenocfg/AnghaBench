#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int initialized; TYPE_2__* driver; } ;
typedef  TYPE_1__ git_merge_driver_entry ;
struct TYPE_8__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  drivers; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* shutdown ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_MERGE ; 
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ git_rwlock_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_rwlock_wrunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_remove (int /*<<< orphan*/ *,size_t) ; 
 TYPE_4__ merge_driver_registry ; 
 TYPE_1__* merge_driver_registry_lookup (size_t*,char const*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

int git_merge_driver_unregister(const char *name)
{
	git_merge_driver_entry *entry;
	size_t pos;
	int error = 0;

	if (git_rwlock_wrlock(&merge_driver_registry.lock) < 0) {
		git_error_set(GIT_ERROR_OS, "failed to lock merge driver registry");
		return -1;
	}

	if ((entry = merge_driver_registry_lookup(&pos, name)) == NULL) {
		git_error_set(GIT_ERROR_MERGE, "cannot find merge driver '%s' to unregister",
			name);
		error = GIT_ENOTFOUND;
		goto done;
	}

	git_vector_remove(&merge_driver_registry.drivers, pos);

	if (entry->initialized && entry->driver->shutdown) {
		entry->driver->shutdown(entry->driver);
		entry->initialized = false;
	}

	git__free(entry);

done:
	git_rwlock_wrunlock(&merge_driver_registry.lock);
	return error;
}