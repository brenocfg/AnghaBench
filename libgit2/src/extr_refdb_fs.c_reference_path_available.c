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
struct packref {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  refcache; } ;
typedef  TYPE_1__ refdb_fs_backend ;
typedef  int /*<<< orphan*/  git_refdb_backend ;

/* Variables and functions */
 int GIT_EEXISTS ; 
 int /*<<< orphan*/  GIT_ERROR_REFERENCE ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 struct packref* git_sortedcache_entry (int /*<<< orphan*/ ,size_t) ; 
 size_t git_sortedcache_entrycount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_sortedcache_rlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_sortedcache_runlock (int /*<<< orphan*/ ) ; 
 int packed_reload (TYPE_1__*) ; 
 int /*<<< orphan*/  ref_is_available (char const*,char const*,int /*<<< orphan*/ ) ; 
 int refdb_fs_backend__exists (int*,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int reference_path_available(
	refdb_fs_backend *backend,
	const char *new_ref,
	const char* old_ref,
	int force)
{
	size_t i;
	int error;

	if ((error = packed_reload(backend)) < 0)
		return error;

	if (!force) {
		int exists;

		if ((error = refdb_fs_backend__exists(
			&exists, (git_refdb_backend *)backend, new_ref)) < 0) {
			return error;
		}

		if (exists) {
			git_error_set(GIT_ERROR_REFERENCE,
				"failed to write reference '%s': a reference with "
				"that name already exists.", new_ref);
			return GIT_EEXISTS;
		}
	}

	git_sortedcache_rlock(backend->refcache);

	for (i = 0; i < git_sortedcache_entrycount(backend->refcache); ++i) {
		struct packref *ref = git_sortedcache_entry(backend->refcache, i);

		if (ref && !ref_is_available(old_ref, new_ref, ref->name)) {
			git_sortedcache_runlock(backend->refcache);
			git_error_set(GIT_ERROR_REFERENCE,
				"path to reference '%s' collides with existing one", new_ref);
			return -1;
		}
	}

	git_sortedcache_runlock(backend->refcache);
	return 0;
}