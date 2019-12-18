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
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_config_level_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* free ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ git_config_backend ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 scalar_t__ ENOTDIR ; 
 int /*<<< orphan*/  GIT_ERROR_CONFIG ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 int git_config_add_backend (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ git_config_backend_from_file (TYPE_1__**,char const*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 int p_stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

int git_config_add_file_ondisk(
	git_config *cfg,
	const char *path,
	git_config_level_t level,
	const git_repository *repo,
	int force)
{
	git_config_backend *file = NULL;
	struct stat st;
	int res;

	assert(cfg && path);

	res = p_stat(path, &st);
	if (res < 0 && errno != ENOENT && errno != ENOTDIR) {
		git_error_set(GIT_ERROR_CONFIG, "failed to stat '%s'", path);
		return -1;
	}

	if (git_config_backend_from_file(&file, path) < 0)
		return -1;

	if ((res = git_config_add_backend(cfg, file, level, repo, force)) < 0) {
		/*
		 * free manually; the file is not owned by the config
		 * instance yet and will not be freed on cleanup
		 */
		file->free(file);
		return res;
	}

	return 0;
}