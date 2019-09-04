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
struct repository {TYPE_1__* submodule_cache; } ;
struct TYPE_2__ {int /*<<< orphan*/  gitmodules_read; } ;

/* Variables and functions */
 int /*<<< orphan*/  repo_read_gitmodules (struct repository*) ; 
 int /*<<< orphan*/  submodule_cache_check_init (struct repository*) ; 

__attribute__((used)) static void gitmodules_read_check(struct repository *repo)
{
	submodule_cache_check_init(repo);

	/* read the repo's .gitmodules file if it hasn't been already */
	if (!repo->submodule_cache->gitmodules_read)
		repo_read_gitmodules(repo);
}