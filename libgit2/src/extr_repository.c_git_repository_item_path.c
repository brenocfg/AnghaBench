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
struct TYPE_2__ {scalar_t__ directory; scalar_t__ name; int /*<<< orphan*/  fallback; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 scalar_t__ git_buf_joinpath (int /*<<< orphan*/ *,char const*,scalar_t__) ; 
 scalar_t__ git_buf_sets (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ git_path_to_dir (int /*<<< orphan*/ *) ; 
 TYPE_1__* items ; 
 char* resolved_parent_path (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int git_repository_item_path(git_buf *out, const git_repository *repo, git_repository_item_t item)
{
	const char *parent = resolved_parent_path(repo, items[item].parent, items[item].fallback);
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