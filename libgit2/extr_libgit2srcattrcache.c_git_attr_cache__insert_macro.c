#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_strmap ;
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_10__ {int /*<<< orphan*/  pattern; } ;
struct TYPE_9__ {scalar_t__ length; } ;
struct TYPE_11__ {TYPE_2__ match; TYPE_1__ assigns; } ;
typedef  TYPE_3__ git_attr_rule ;
struct TYPE_12__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * macros; } ;
typedef  TYPE_4__ git_attr_cache ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 scalar_t__ attr_cache_lock (TYPE_4__*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_4__* git_repository_attr_cache (int /*<<< orphan*/ *) ; 
 int git_strmap_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 

int git_attr_cache__insert_macro(git_repository *repo, git_attr_rule *macro)
{
	git_attr_cache *cache = git_repository_attr_cache(repo);
	git_strmap *macros = cache->macros;
	int error;

	/* TODO: generate warning log if (macro->assigns.length == 0) */
	if (macro->assigns.length == 0)
		return 0;

	if (attr_cache_lock(cache) < 0) {
		git_error_set(GIT_ERROR_OS, "unable to get attr cache lock");
		error = -1;
	} else {
		error = git_strmap_set(macros, macro->match.pattern, macro);
		git_mutex_unlock(&cache->lock);
	}

	return error;
}