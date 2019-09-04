#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/ * file; } ;
typedef  TYPE_2__ git_attr_file_entry ;
struct TYPE_14__ {size_t source; TYPE_1__* entry; } ;
typedef  TYPE_3__ git_attr_file ;
typedef  int /*<<< orphan*/  git_attr_cache ;
struct TYPE_12__ {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_REFCOUNT_INC (TYPE_3__*) ; 
 int /*<<< orphan*/  GIT_REFCOUNT_OWN (TYPE_3__*,TYPE_2__*) ; 
 scalar_t__ attr_cache_lock (int /*<<< orphan*/ *) ; 
 TYPE_2__* attr_cache_lookup_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  attr_cache_unlock (int /*<<< orphan*/ *) ; 
 TYPE_3__* git__swap (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  git_attr_file__free (TYPE_3__*) ; 

__attribute__((used)) static int attr_cache_upsert(git_attr_cache *cache, git_attr_file *file)
{
	git_attr_file_entry *entry;
	git_attr_file *old;

	if (attr_cache_lock(cache) < 0)
		return -1;

	entry = attr_cache_lookup_entry(cache, file->entry->path);

	GIT_REFCOUNT_OWN(file, entry);
	GIT_REFCOUNT_INC(file);

	/*
	 * Replace the existing value if another thread has
	 * created it in the meantime.
	 */
	old = git__swap(entry->file[file->source], file);

	if (old) {
		GIT_REFCOUNT_OWN(old, NULL);
		git_attr_file__free(old);
	}

	attr_cache_unlock(cache);
	return 0;
}