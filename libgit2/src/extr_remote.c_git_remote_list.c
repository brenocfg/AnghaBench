#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_vector ;
struct TYPE_3__ {char** strings; int /*<<< orphan*/  count; } ;
typedef  TYPE_1__ git_strarray ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_VECTOR_INIT ; 
 int /*<<< orphan*/  git__free ; 
 int /*<<< orphan*/  git__strcmp_cb ; 
 int git_config_foreach_match (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int git_repository_config__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ git_vector_detach (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_free_deep (int /*<<< orphan*/ *) ; 
 int git_vector_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_vector_uniq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remote_list_cb ; 

int git_remote_list(git_strarray *remotes_list, git_repository *repo)
{
	int error;
	git_config *cfg;
	git_vector list = GIT_VECTOR_INIT;

	if ((error = git_repository_config__weakptr(&cfg, repo)) < 0)
		return error;

	if ((error = git_vector_init(&list, 4, git__strcmp_cb)) < 0)
		return error;

	error = git_config_foreach_match(
		cfg, "^remote\\..*\\.(push)?url$", remote_list_cb, &list);

	if (error < 0) {
		git_vector_free_deep(&list);
		return error;
	}

	git_vector_uniq(&list, git__free);

	remotes_list->strings =
		(char **)git_vector_detach(&remotes_list->count, NULL, &list);

	return 0;
}