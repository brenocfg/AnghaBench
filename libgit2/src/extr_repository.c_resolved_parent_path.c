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
typedef  int git_repository_item_t ;
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
#define  GIT_REPOSITORY_ITEM_COMMONDIR 130 
#define  GIT_REPOSITORY_ITEM_GITDIR 129 
#define  GIT_REPOSITORY_ITEM_WORKDIR 128 
 int GIT_REPOSITORY_ITEM__LAST ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 char* git_repository_commondir (int /*<<< orphan*/  const*) ; 
 char* git_repository_path (int /*<<< orphan*/  const*) ; 
 char* git_repository_workdir (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static const char *resolved_parent_path(const git_repository *repo, git_repository_item_t item, git_repository_item_t fallback)
{
	const char *parent;

	switch (item) {
		case GIT_REPOSITORY_ITEM_GITDIR:
			parent = git_repository_path(repo);
			break;
		case GIT_REPOSITORY_ITEM_WORKDIR:
			parent = git_repository_workdir(repo);
			break;
		case GIT_REPOSITORY_ITEM_COMMONDIR:
			parent = git_repository_commondir(repo);
			break;
		default:
			git_error_set(GIT_ERROR_INVALID, "invalid item directory");
			return NULL;
	}
	if (!parent && fallback != GIT_REPOSITORY_ITEM__LAST)
		return resolved_parent_path(repo, fallback, GIT_REPOSITORY_ITEM__LAST);

	return parent;
}