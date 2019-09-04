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
struct TYPE_3__ {int is_bare; int /*<<< orphan*/  is_worktree; } ;
typedef  TYPE_1__ git_repository ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int git_config_get_bool (int*,int /*<<< orphan*/  const*,char*) ; 

__attribute__((used)) static int load_config_data(git_repository *repo, const git_config *config)
{
	int is_bare;

	int err = git_config_get_bool(&is_bare, config, "core.bare");
	if (err < 0 && err != GIT_ENOTFOUND)
		return err;

	/* Try to figure out if it's bare, default to non-bare if it's not set */
	if (err != GIT_ENOTFOUND)
		repo->is_bare = is_bare && !repo->is_worktree;
	else
		repo->is_bare = 0;

	return 0;
}