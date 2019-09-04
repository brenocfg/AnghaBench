#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct git_pack_file {int /*<<< orphan*/  pack_name; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int /*<<< orphan*/  git__free (char*) ; 
 int /*<<< orphan*/  git__mwindow_mutex ; 
 int /*<<< orphan*/  git__pack_cache ; 
 int /*<<< orphan*/  git_atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ git_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_mutex_unlock (int /*<<< orphan*/ *) ; 
 int git_packfile__name (char**,char const*) ; 
 int git_packfile_alloc (struct git_pack_file**,char const*) ; 
 int /*<<< orphan*/  git_packfile_free (struct git_pack_file*) ; 
 struct git_pack_file* git_strmap_get (int /*<<< orphan*/ ,char*) ; 
 int git_strmap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct git_pack_file*) ; 

int git_mwindow_get_pack(struct git_pack_file **out, const char *path)
{
	struct git_pack_file *pack;
	char *packname;
	int error;

	if ((error = git_packfile__name(&packname, path)) < 0)
		return error;

	if (git_mutex_lock(&git__mwindow_mutex) < 0) {
		git_error_set(GIT_ERROR_OS, "failed to lock mwindow mutex");
		return -1;
	}

	pack = git_strmap_get(git__pack_cache, packname);
	git__free(packname);

	if (pack != NULL) {
		git_atomic_inc(&pack->refcount);
		git_mutex_unlock(&git__mwindow_mutex);
		*out = pack;
		return 0;
	}

	/* If we didn't find it, we need to create it */
	if ((error = git_packfile_alloc(&pack, path)) < 0) {
		git_mutex_unlock(&git__mwindow_mutex);
		return error;
	}

	git_atomic_inc(&pack->refcount);

	error = git_strmap_set(git__pack_cache, pack->pack_name, pack);
	git_mutex_unlock(&git__mwindow_mutex);

	if (error < 0) {
		git_packfile_free(pack);
		return -1;
	}

	*out = pack;
	return 0;
}