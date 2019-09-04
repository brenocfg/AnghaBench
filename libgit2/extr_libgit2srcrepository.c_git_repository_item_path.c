#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t git_repository_item_t ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_buf ;
struct TYPE_2__ {int parent; scalar_t__ directory; scalar_t__ name; } ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
#define  GIT_REPOSITORY_ITEM_COMMONDIR 130 
#define  GIT_REPOSITORY_ITEM_GITDIR 129 
#define  GIT_REPOSITORY_ITEM_WORKDIR 128 
 scalar_t__ git_buf_joinpath (int /*<<< orphan*/ *,char const*,scalar_t__) ; 
 scalar_t__ git_buf_sets (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ git_path_to_dir (int /*<<< orphan*/ *) ; 
 char* git_repository_commondir (int /*<<< orphan*/  const*) ; 
 char* git_repository_path (int /*<<< orphan*/  const*) ; 
 char* git_repository_workdir (int /*<<< orphan*/  const*) ; 
 TYPE_1__* items ; 

int git_repository_item_path(git_buf *out, const git_repository *repo, git_repository_item_t item)
{
	const char *parent;

	switch (items[item].parent) {
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
			return -1;
	}

	if (parent == NULL) {
		git_error_set(GIT_ERROR_INVALID, "path cannot exist in repository");
		return GIT_ENOTFOUND;
	}

	if (git_buf_sets(out, parent) < 0)
		return -1;

	if (items[item].name) {
		if (git_buf_joinpath(out, parent, items[item].name) < 0)
			return -1;
	}

	if (items[item].directory) {
		if (git_path_to_dir(out) < 0)
			return -1;
	}

	return 0;
}