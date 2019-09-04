#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct packref {int /*<<< orphan*/  peel; int /*<<< orphan*/  oid; } ;
struct TYPE_4__ {int /*<<< orphan*/  refcache; } ;
typedef  TYPE_1__ refdb_fs_backend ;
typedef  int /*<<< orphan*/  git_reference ;

/* Variables and functions */
 int /*<<< orphan*/ * git_reference__alloc (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct packref* git_sortedcache_lookup (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ git_sortedcache_rlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_sortedcache_runlock (int /*<<< orphan*/ ) ; 
 int packed_reload (TYPE_1__*) ; 
 int ref_error_notfound (char const*) ; 

__attribute__((used)) static int packed_lookup(
	git_reference **out,
	refdb_fs_backend *backend,
	const char *ref_name)
{
	int error = 0;
	struct packref *entry;

	if ((error = packed_reload(backend)) < 0)
		return error;

	if (git_sortedcache_rlock(backend->refcache) < 0)
		return -1;

	entry = git_sortedcache_lookup(backend->refcache, ref_name);
	if (!entry) {
		error = ref_error_notfound(ref_name);
	} else {
		*out = git_reference__alloc(ref_name, &entry->oid, &entry->peel);
		if (!*out)
			error = -1;
	}

	git_sortedcache_runlock(backend->refcache);

	return error;
}