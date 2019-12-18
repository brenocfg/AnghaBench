#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_12__ {int /*<<< orphan*/  pattern; } ;
struct TYPE_13__ {scalar_t__ length; } ;
struct TYPE_14__ {TYPE_1__ match; TYPE_2__ assigns; } ;
typedef  TYPE_3__ git_attr_rule ;
struct TYPE_15__ {int /*<<< orphan*/  macros; } ;
typedef  TYPE_4__ git_attr_cache ;

/* Variables and functions */
 int attr_cache_lock (TYPE_4__*) ; 
 int /*<<< orphan*/  attr_cache_unlock (TYPE_4__*) ; 
 int /*<<< orphan*/  git_attr_rule__free (TYPE_3__*) ; 
 TYPE_4__* git_repository_attr_cache (int /*<<< orphan*/ *) ; 
 TYPE_3__* git_strmap_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int git_strmap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 

int git_attr_cache__insert_macro(git_repository *repo, git_attr_rule *macro)
{
	git_attr_cache *cache = git_repository_attr_cache(repo);
	git_attr_rule *preexisting;
	bool locked = false;
	int error = 0;

	/*
	 * Callers assume that if we return success, that the
	 * macro will have been adopted by the attributes cache.
	 * Thus, we have to free the macro here if it's not being
	 * added to the cache.
	 *
	 * TODO: generate warning log if (macro->assigns.length == 0)
	 */
	if (macro->assigns.length == 0) {
		git_attr_rule__free(macro);
		goto out;
	}

	if ((error = attr_cache_lock(cache)) < 0)
		goto out;
	locked = true;

	if ((preexisting = git_strmap_get(cache->macros, macro->match.pattern)) != NULL)
	    git_attr_rule__free(preexisting);

	if ((error = git_strmap_set(cache->macros, macro->match.pattern, macro)) < 0)
	    goto out;

out:
	if (locked)
		attr_cache_unlock(cache);
	return error;
}