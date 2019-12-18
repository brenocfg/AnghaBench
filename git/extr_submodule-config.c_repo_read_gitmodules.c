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
struct repository {TYPE_1__* submodule_cache; int /*<<< orphan*/  index; } ;
struct TYPE_2__ {int gitmodules_read; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_from_gitmodules (int /*<<< orphan*/ ,struct repository*,struct repository*) ; 
 int /*<<< orphan*/  gitmodules_cb ; 
 int /*<<< orphan*/  is_gitmodules_unmerged (int /*<<< orphan*/ ) ; 
 scalar_t__ repo_read_index (struct repository*) ; 
 int /*<<< orphan*/  submodule_cache_check_init (struct repository*) ; 

void repo_read_gitmodules(struct repository *repo)
{
	submodule_cache_check_init(repo);

	if (repo_read_index(repo) < 0)
		return;

	if (!is_gitmodules_unmerged(repo->index))
		config_from_gitmodules(gitmodules_cb, repo, repo);

	repo->submodule_cache->gitmodules_read = 1;
}