#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  objects; } ;
typedef  TYPE_1__ git_repository ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  git_attr_cache_flush (TYPE_1__*) ; 
 int /*<<< orphan*/  git_cache_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_submodule_cache_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  set_config (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_index (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_odb (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_refdb (TYPE_1__*,int /*<<< orphan*/ *) ; 

void git_repository__cleanup(git_repository *repo)
{
	assert(repo);

	git_repository_submodule_cache_clear(repo);
	git_cache_clear(&repo->objects);
	git_attr_cache_flush(repo);

	set_config(repo, NULL);
	set_index(repo, NULL);
	set_odb(repo, NULL);
	set_refdb(repo, NULL);
}