#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  attrcache; } ;
typedef  TYPE_1__ git_repository ;
typedef  int /*<<< orphan*/  git_config ;
struct TYPE_15__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  macros; int /*<<< orphan*/  files; int /*<<< orphan*/  cfg_excl_file; int /*<<< orphan*/  cfg_attr_file; int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ git_attr_cache ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ATTR_CONFIG ; 
 int /*<<< orphan*/  GIT_ATTR_FILE_XDG ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_2__*) ; 
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int /*<<< orphan*/  GIT_IGNORE_CONFIG ; 
 int /*<<< orphan*/  GIT_IGNORE_FILE_XDG ; 
 int /*<<< orphan*/  attr_cache__free (TYPE_2__*) ; 
 int attr_cache__lookup_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* git__calloc (int,int) ; 
 TYPE_2__* git__compare_and_swap (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  git__free (TYPE_2__*) ; 
 int git_attr_add_macro (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ git_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pool_init (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* git_repository_attr_cache (TYPE_1__*) ; 
 int git_repository_config_snapshot (int /*<<< orphan*/ **,TYPE_1__*) ; 
 int git_strmap_new (int /*<<< orphan*/ *) ; 

int git_attr_cache__init(git_repository *repo)
{
	int ret = 0;
	git_attr_cache *cache = git_repository_attr_cache(repo);
	git_config *cfg = NULL;

	if (cache)
		return 0;

	cache = git__calloc(1, sizeof(git_attr_cache));
	GIT_ERROR_CHECK_ALLOC(cache);

	/* set up lock */
	if (git_mutex_init(&cache->lock) < 0) {
		git_error_set(GIT_ERROR_OS, "unable to initialize lock for attr cache");
		git__free(cache);
		return -1;
	}

	if ((ret = git_repository_config_snapshot(&cfg, repo)) < 0)
		goto cancel;

	/* cache config settings for attributes and ignores */
	ret = attr_cache__lookup_path(
		&cache->cfg_attr_file, cfg, GIT_ATTR_CONFIG, GIT_ATTR_FILE_XDG);
	if (ret < 0)
		goto cancel;

	ret = attr_cache__lookup_path(
		&cache->cfg_excl_file, cfg, GIT_IGNORE_CONFIG, GIT_IGNORE_FILE_XDG);
	if (ret < 0)
		goto cancel;

	/* allocate hashtable for attribute and ignore file contents,
	 * hashtable for attribute macros, and string pool
	 */
	if ((ret = git_strmap_new(&cache->files)) < 0 ||
	    (ret = git_strmap_new(&cache->macros)) < 0)
		goto cancel;

	git_pool_init(&cache->pool, 1);

	cache = git__compare_and_swap(&repo->attrcache, NULL, cache);
	if (cache)
		goto cancel; /* raced with another thread, free this but no error */

	git_config_free(cfg);

	/* insert default macros */
	return git_attr_add_macro(repo, "binary", "-diff -crlf -text");

cancel:
	attr_cache__free(cache);
	git_config_free(cfg);
	return ret;
}