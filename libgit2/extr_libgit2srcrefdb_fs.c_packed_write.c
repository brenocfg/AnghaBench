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
struct packref {int dummy; } ;
struct TYPE_5__ {scalar_t__ fsync; int /*<<< orphan*/ * refcache; } ;
typedef  TYPE_1__ refdb_fs_backend ;
typedef  int /*<<< orphan*/  git_sortedcache ;
typedef  int /*<<< orphan*/  git_filebuf ;

/* Variables and functions */
 int GIT_FILEBUF_FSYNC ; 
 int /*<<< orphan*/  GIT_FILEBUF_INIT ; 
 int /*<<< orphan*/  GIT_PACKEDREFS_FILE_MODE ; 
 int /*<<< orphan*/  GIT_PACKEDREFS_HEADER ; 
 int /*<<< orphan*/  assert (struct packref*) ; 
 int /*<<< orphan*/  git_filebuf_cleanup (int /*<<< orphan*/ *) ; 
 int git_filebuf_commit (int /*<<< orphan*/ *) ; 
 int git_filebuf_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int git_filebuf_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct packref* git_sortedcache_entry (int /*<<< orphan*/ *,size_t) ; 
 size_t git_sortedcache_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_sortedcache_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_sortedcache_updated (int /*<<< orphan*/ *) ; 
 int git_sortedcache_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_sortedcache_wunlock (int /*<<< orphan*/ *) ; 
 int packed_find_peel (TYPE_1__*,struct packref*) ; 
 int packed_remove_loose (TYPE_1__*) ; 
 int packed_write_ref (struct packref*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int packed_write(refdb_fs_backend *backend)
{
	git_sortedcache *refcache = backend->refcache;
	git_filebuf pack_file = GIT_FILEBUF_INIT;
	int error, open_flags = 0;
	size_t i;

	/* lock the cache to updates while we do this */
	if ((error = git_sortedcache_wlock(refcache)) < 0)
		return error;

	if (backend->fsync)
		open_flags = GIT_FILEBUF_FSYNC;

	/* Open the file! */
	if ((error = git_filebuf_open(&pack_file, git_sortedcache_path(refcache), open_flags, GIT_PACKEDREFS_FILE_MODE)) < 0)
		goto fail;

	/* Packfiles have a header... apparently
	 * This is in fact not required, but we might as well print it
	 * just for kicks */
	if ((error = git_filebuf_printf(&pack_file, "%s\n", GIT_PACKEDREFS_HEADER)) < 0)
		goto fail;

	for (i = 0; i < git_sortedcache_entrycount(refcache); ++i) {
		struct packref *ref = git_sortedcache_entry(refcache, i);
		assert(ref);

		if ((error = packed_find_peel(backend, ref)) < 0)
			goto fail;

		if ((error = packed_write_ref(ref, &pack_file)) < 0)
			goto fail;
	}

	/* if we've written all the references properly, we can commit
	 * the packfile to make the changes effective */
	if ((error = git_filebuf_commit(&pack_file)) < 0)
		goto fail;

	/* when and only when the packfile has been properly written,
	 * we can go ahead and remove the loose refs */
	if ((error = packed_remove_loose(backend)) < 0)
		goto fail;

	git_sortedcache_updated(refcache);
	git_sortedcache_wunlock(refcache);

	/* we're good now */
	return 0;

fail:
	git_filebuf_cleanup(&pack_file);
	git_sortedcache_wunlock(refcache);

	return error;
}