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
struct repository {TYPE_1__* submodule_cache; } ;
struct TYPE_3__ {scalar_t__ initialized; } ;

/* Variables and functions */
 TYPE_1__* submodule_cache_alloc () ; 
 int /*<<< orphan*/  submodule_cache_init (TYPE_1__*) ; 

__attribute__((used)) static void submodule_cache_check_init(struct repository *repo)
{
	if (repo->submodule_cache && repo->submodule_cache->initialized)
		return;

	if (!repo->submodule_cache)
		repo->submodule_cache = submodule_cache_alloc();

	submodule_cache_init(repo->submodule_cache);
}