#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_index ;
struct TYPE_12__ {char const* ptr; } ;
typedef  TYPE_1__ git_buf ;
struct TYPE_13__ {int init_setup; } ;
typedef  TYPE_2__ git_attr_session ;
struct TYPE_14__ {char const* cfg_attr_file; } ;

/* Variables and functions */
 int GIT_ATTR_CHECK_INCLUDE_HEAD ; 
 char const* GIT_ATTR_FILE ; 
 char const* GIT_ATTR_FILE_INREPO ; 
 int /*<<< orphan*/  GIT_ATTR_FILE__FROM_FILE ; 
 int /*<<< orphan*/  GIT_ATTR_FILE__FROM_HEAD ; 
 int /*<<< orphan*/  GIT_ATTR_FILE__FROM_INDEX ; 
 TYPE_1__ GIT_BUF_INIT ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_REPOSITORY_ITEM_INFO ; 
 int git_attr_cache__init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 TYPE_7__* git_repository_attr_cache (int /*<<< orphan*/ *) ; 
 int git_repository_index__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int git_repository_item_path (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* git_repository_workdir (int /*<<< orphan*/ *) ; 
 int preload_attr_file (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,char const*,char const*,int) ; 
 int system_attr_file (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static int attr_setup(
	git_repository *repo,
	git_attr_session *attr_session,
	uint32_t flags)
{
	git_buf path = GIT_BUF_INIT;
	git_index *idx = NULL;
	const char *workdir;
	int error = 0;

	if (attr_session && attr_session->init_setup)
		return 0;

	if ((error = git_attr_cache__init(repo)) < 0)
		return error;

	/*
	 * Preload attribute files that could contain macros so the
	 * definitions will be available for later file parsing.
	 */

	if ((error = system_attr_file(&path, attr_session)) < 0 ||
	    (error = preload_attr_file(repo, attr_session, GIT_ATTR_FILE__FROM_FILE,
				       NULL, path.ptr, true)) < 0) {
		if (error != GIT_ENOTFOUND)
			goto out;
	}

	if ((error = preload_attr_file(repo, attr_session, GIT_ATTR_FILE__FROM_FILE,
				       NULL, git_repository_attr_cache(repo)->cfg_attr_file, true)) < 0)
		goto out;

	git_buf_clear(&path); /* git_repository_item_path expects an empty buffer, because it uses git_buf_set */
	if ((error = git_repository_item_path(&path, repo, GIT_REPOSITORY_ITEM_INFO)) < 0 ||
	    (error = preload_attr_file(repo, attr_session, GIT_ATTR_FILE__FROM_FILE,
				       path.ptr, GIT_ATTR_FILE_INREPO, true)) < 0) {
		if (error != GIT_ENOTFOUND)
			goto out;
	}

	if ((workdir = git_repository_workdir(repo)) != NULL &&
	    (error = preload_attr_file(repo, attr_session, GIT_ATTR_FILE__FROM_FILE,
				       workdir, GIT_ATTR_FILE, true)) < 0)
			goto out;

	if ((error = git_repository_index__weakptr(&idx, repo)) < 0 ||
	    (error = preload_attr_file(repo, attr_session, GIT_ATTR_FILE__FROM_INDEX,
				       NULL, GIT_ATTR_FILE, true)) < 0)
			goto out;

	if ((flags & GIT_ATTR_CHECK_INCLUDE_HEAD) != 0 &&
	    (error = preload_attr_file(repo, attr_session, GIT_ATTR_FILE__FROM_HEAD,
				       NULL, GIT_ATTR_FILE, true)) < 0)
		goto out;

	if (attr_session)
		attr_session->init_setup = 1;

out:
	git_buf_dispose(&path);

	return error;
}