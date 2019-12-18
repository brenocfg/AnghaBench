#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  refcache; } ;
typedef  TYPE_1__ refdb_fs_backend ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int git_sortedcache_lookup_index (size_t*,int /*<<< orphan*/ ,char const*) ; 
 int git_sortedcache_remove (int /*<<< orphan*/ ,size_t) ; 
 int git_sortedcache_wlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_sortedcache_wunlock (int /*<<< orphan*/ ) ; 
 int packed_reload (TYPE_1__*) ; 
 int packed_write (TYPE_1__*) ; 

__attribute__((used)) static int packed_delete(refdb_fs_backend *backend, const char *ref_name)
{
	size_t pack_pos;
	int error, found = 0;

	if ((error = packed_reload(backend)) < 0)
		goto cleanup;

	if ((error = git_sortedcache_wlock(backend->refcache)) < 0)
		goto cleanup;

	/* If a packed reference exists, remove it from the packfile and repack if necessary */
	error = git_sortedcache_lookup_index(&pack_pos, backend->refcache, ref_name);
	if (error == 0) {
		error = git_sortedcache_remove(backend->refcache, pack_pos);
		found = 1;
	}
	if (error == GIT_ENOTFOUND)
		error = 0;

	git_sortedcache_wunlock(backend->refcache);

	if (found)
		error = packed_write(backend);

cleanup:
	return error;
}