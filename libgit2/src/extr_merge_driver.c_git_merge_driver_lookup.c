#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int initialized; TYPE_2__* driver; } ;
typedef  TYPE_1__ git_merge_driver_entry ;
struct TYPE_10__ {int (* initialize ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ git_merge_driver ;
struct TYPE_12__ {TYPE_2__ base; } ;
struct TYPE_11__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_MERGE ; 
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__ git_merge_driver__binary ; 
 TYPE_7__ git_merge_driver__text ; 
 scalar_t__ git_rwlock_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_rwlock_rdunlock (int /*<<< orphan*/ *) ; 
 char const* merge_driver_name__binary ; 
 char const* merge_driver_name__text ; 
 TYPE_5__ merge_driver_registry ; 
 TYPE_1__* merge_driver_registry_lookup (size_t*,char const*) ; 
 int stub1 (TYPE_2__*) ; 

git_merge_driver *git_merge_driver_lookup(const char *name)
{
	git_merge_driver_entry *entry;
	size_t pos;
	int error;

	/* If we've decided the merge driver to use internally - and not
	 * based on user configuration (in merge_driver_name_for_path)
	 * then we can use a hardcoded name to compare instead of bothering
	 * to take a lock and look it up in the vector.
	 */
	if (name == merge_driver_name__text)
		return &git_merge_driver__text.base;
	else if (name == merge_driver_name__binary)
		return &git_merge_driver__binary;

	if (git_rwlock_rdlock(&merge_driver_registry.lock) < 0) {
		git_error_set(GIT_ERROR_OS, "failed to lock merge driver registry");
		return NULL;
	}

	entry = merge_driver_registry_lookup(&pos, name);

	git_rwlock_rdunlock(&merge_driver_registry.lock);

	if (entry == NULL) {
		git_error_set(GIT_ERROR_MERGE, "cannot use an unregistered filter");
		return NULL;
	}

	if (!entry->initialized) {
		if (entry->driver->initialize &&
			(error = entry->driver->initialize(entry->driver)) < 0)
			return NULL;

		entry->initialized = 1;
	}

	return entry->driver;
}