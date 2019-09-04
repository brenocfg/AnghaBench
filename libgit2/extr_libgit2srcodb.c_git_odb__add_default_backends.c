#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct stat {scalar_t__ st_ino; } ;
typedef  scalar_t__ ino_t ;
typedef  int /*<<< orphan*/  git_odb_backend ;
struct TYPE_10__ {size_t length; } ;
struct TYPE_8__ {int /*<<< orphan*/  do_fsync; TYPE_5__ backends; } ;
typedef  TYPE_1__ git_odb ;
struct TYPE_9__ {scalar_t__ disk_inode; } ;
typedef  TYPE_2__ backend_internal ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_ODB ; 
 int /*<<< orphan*/  GIT_LOOSE_PRIORITY ; 
 int /*<<< orphan*/  GIT_PACKED_PRIORITY ; 
 scalar_t__ add_backend_internal (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ git_odb_backend_loose (int /*<<< orphan*/ **,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ git_odb_backend_pack (int /*<<< orphan*/ **,char const*) ; 
 TYPE_2__* git_vector_get (TYPE_5__*,size_t) ; 
 int load_alternates (TYPE_1__*,char const*,int) ; 
 scalar_t__ p_stat (char const*,struct stat*) ; 

int git_odb__add_default_backends(
	git_odb *db, const char *objects_dir,
	bool as_alternates, int alternate_depth)
{
	size_t i;
	struct stat st;
	ino_t inode;
	git_odb_backend *loose, *packed;

	/* TODO: inodes are not really relevant on Win32, so we need to find
	 * a cross-platform workaround for this */
#ifdef GIT_WIN32
	GIT_UNUSED(i);
	GIT_UNUSED(st);

	inode = 0;
#else
	if (p_stat(objects_dir, &st) < 0) {
		if (as_alternates)
			return 0;

		git_error_set(GIT_ERROR_ODB, "failed to load object database in '%s'", objects_dir);
		return -1;
	}

	inode = st.st_ino;

	for (i = 0; i < db->backends.length; ++i) {
		backend_internal *backend = git_vector_get(&db->backends, i);
		if (backend->disk_inode == inode)
			return 0;
	}
#endif

	/* add the loose object backend */
	if (git_odb_backend_loose(&loose, objects_dir, -1, db->do_fsync, 0, 0) < 0 ||
		add_backend_internal(db, loose, GIT_LOOSE_PRIORITY, as_alternates, inode) < 0)
		return -1;

	/* add the packed file backend */
	if (git_odb_backend_pack(&packed, objects_dir) < 0 ||
		add_backend_internal(db, packed, GIT_PACKED_PRIORITY, as_alternates, inode) < 0)
		return -1;

	return load_alternates(db, objects_dir, alternate_depth);
}