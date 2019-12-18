#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  git_vector ;
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_14__ {int /*<<< orphan*/ * ptr; } ;
typedef  TYPE_1__ git_buf ;
typedef  int /*<<< orphan*/  git_attr_session ;
struct TYPE_15__ {int flags; char const* workdir; int /*<<< orphan*/ * files; int /*<<< orphan*/  index; int /*<<< orphan*/ * attr_session; int /*<<< orphan*/ * repo; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_2__ attr_walk_up_info ;
struct TYPE_16__ {int /*<<< orphan*/ * cfg_attr_file; } ;

/* Variables and functions */
 int GIT_ATTR_CHECK_NO_SYSTEM ; 
 int /*<<< orphan*/ * GIT_ATTR_FILE_INREPO ; 
 int /*<<< orphan*/  GIT_ATTR_FILE__FROM_FILE ; 
 TYPE_1__ GIT_BUF_INIT ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_REPOSITORY_ITEM_INFO ; 
 int attr_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int git_path_dirname_r (TYPE_1__*,char const*) ; 
 int git_path_find_dir (TYPE_1__*,char const*,char const*) ; 
 int git_path_walk_up (TYPE_1__*,char const*,int (*) (TYPE_2__*,char*),TYPE_2__*) ; 
 TYPE_6__* git_repository_attr_cache (int /*<<< orphan*/ *) ; 
 scalar_t__ git_repository_index__weakptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_repository_item_path (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* git_repository_workdir (int /*<<< orphan*/ *) ; 
 int push_attr_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int push_one_attr (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  release_attr_files (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ *,char*) ; 
 int system_attr_file (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int collect_attr_files(
	git_repository *repo,
	git_attr_session *attr_session,
	uint32_t flags,
	const char *path,
	git_vector *files)
{
	int error = 0;
	git_buf dir = GIT_BUF_INIT, attrfile = GIT_BUF_INIT;
	const char *workdir = git_repository_workdir(repo);
	attr_walk_up_info info = { NULL };

	if ((error = attr_setup(repo, attr_session, flags)) < 0)
		return error;

	/* Resolve path in a non-bare repo */
	if (workdir != NULL)
		error = git_path_find_dir(&dir, path, workdir);
	else
		error = git_path_dirname_r(&dir, path);
	if (error < 0)
		goto cleanup;

	/* in precendence order highest to lowest:
	 * - $GIT_DIR/info/attributes
	 * - path components with .gitattributes
	 * - config core.attributesfile
	 * - $GIT_PREFIX/etc/gitattributes
	 */

	if ((error = git_repository_item_path(&attrfile, repo, GIT_REPOSITORY_ITEM_INFO)) < 0 ||
	    (error = push_attr_file(repo, attr_session, files, GIT_ATTR_FILE__FROM_FILE,
				    attrfile.ptr, GIT_ATTR_FILE_INREPO, true)) < 0) {
		if (error != GIT_ENOTFOUND)
			goto cleanup;
	}

	info.repo = repo;
	info.attr_session = attr_session;
	info.flags = flags;
	info.workdir = workdir;
	if (git_repository_index__weakptr(&info.index, repo) < 0)
		git_error_clear(); /* no error even if there is no index */
	info.files = files;

	if (!strcmp(dir.ptr, "."))
		error = push_one_attr(&info, "");
	else
		error = git_path_walk_up(&dir, workdir, push_one_attr, &info);

	if (error < 0)
		goto cleanup;

	if (git_repository_attr_cache(repo)->cfg_attr_file != NULL) {
		error = push_attr_file(repo, attr_session, files, GIT_ATTR_FILE__FROM_FILE,
				       NULL, git_repository_attr_cache(repo)->cfg_attr_file, true);
		if (error < 0)
			goto cleanup;
	}

	if ((flags & GIT_ATTR_CHECK_NO_SYSTEM) == 0) {
		error = system_attr_file(&dir, attr_session);

		if (!error)
			error = push_attr_file(repo, attr_session, files, GIT_ATTR_FILE__FROM_FILE,
					       NULL, dir.ptr, true);
		else if (error == GIT_ENOTFOUND)
			error = 0;
	}

 cleanup:
	if (error < 0)
		release_attr_files(files);
	git_buf_dispose(&attrfile);
	git_buf_dispose(&dir);

	return error;
}