#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ is_bare; } ;
typedef  TYPE_1__ git_repository ;
typedef  int /*<<< orphan*/  git_mailmap ;
typedef  int /*<<< orphan*/  git_config ;
struct TYPE_12__ {char* ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  MM_BLOB_CONFIG ; 
 char* MM_BLOB_DEFAULT ; 
 char const* MM_FILE ; 
 int /*<<< orphan*/  MM_FILE_CONFIG ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_config_get_path (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ git_config_get_string_buf (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ git_repository_config (int /*<<< orphan*/ **,TYPE_1__*) ; 
 int /*<<< orphan*/  mailmap_add_blob (int /*<<< orphan*/ *,TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  mailmap_add_file_ondisk (int /*<<< orphan*/ *,char const*,TYPE_1__*) ; 

__attribute__((used)) static void mailmap_add_from_repository(git_mailmap *mm, git_repository *repo)
{
	git_config *config = NULL;
	git_buf rev_buf = GIT_BUF_INIT;
	git_buf path_buf = GIT_BUF_INIT;
	const char *rev = NULL;
	const char *path = NULL;

	assert(mm && repo);

	/* If we're in a bare repo, default blob to 'HEAD:.mailmap' */
	if (repo->is_bare)
		rev = MM_BLOB_DEFAULT;

	/* Try to load 'mailmap.file' and 'mailmap.blob' cfgs from the repo */
	if (git_repository_config(&config, repo) == 0) {
		if (git_config_get_string_buf(&rev_buf, config, MM_BLOB_CONFIG) == 0)
			rev = rev_buf.ptr;
		if (git_config_get_path(&path_buf, config, MM_FILE_CONFIG) == 0)
			path = path_buf.ptr;
	}

	/*
	 * Load mailmap files in order, overriding previous entries with new ones.
	 *  1. The '.mailmap' file in the repository's workdir root,
	 *  2. The blob described by the 'mailmap.blob' config (default HEAD:.mailmap),
	 *  3. The file described by the 'mailmap.file' config.
	 *
	 * We ignore errors from these loads, as these files may not exist, or may
	 * contain invalid information, and we don't want to report that error.
	 *
	 * XXX: Warn?
	 */
	if (!repo->is_bare)
		mailmap_add_file_ondisk(mm, MM_FILE, repo);
	if (rev != NULL)
		mailmap_add_blob(mm, repo, rev);
	if (path != NULL)
		mailmap_add_file_ondisk(mm, path, repo);

	git_buf_dispose(&rev_buf);
	git_buf_dispose(&path_buf);
	git_config_free(config);
}