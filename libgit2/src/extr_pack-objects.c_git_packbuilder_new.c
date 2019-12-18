#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct walk_object {int dummy; } ;
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_7__ {int nr_threads; int /*<<< orphan*/  progress_cond; int /*<<< orphan*/  progress_mutex; int /*<<< orphan*/  cache_mutex; int /*<<< orphan*/  odb; int /*<<< orphan*/  zstream; int /*<<< orphan*/  ctx; int /*<<< orphan*/ * repo; int /*<<< orphan*/  object_pool; int /*<<< orphan*/  walk_objects; int /*<<< orphan*/  object_ix; } ;
typedef  TYPE_1__ git_packbuilder ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int /*<<< orphan*/  GIT_ZSTREAM_DEFLATE ; 
 TYPE_1__* git__calloc (int,int) ; 
 scalar_t__ git_cond_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ git_hash_ctx_init (int /*<<< orphan*/ *) ; 
 scalar_t__ git_mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ git_oidmap_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_packbuilder_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_pool_init (int /*<<< orphan*/ *,int) ; 
 scalar_t__ git_repository_odb (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ git_zstream_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ packbuilder_config (TYPE_1__*) ; 

int git_packbuilder_new(git_packbuilder **out, git_repository *repo)
{
	git_packbuilder *pb;

	*out = NULL;

	pb = git__calloc(1, sizeof(*pb));
	GIT_ERROR_CHECK_ALLOC(pb);

	if (git_oidmap_new(&pb->object_ix) < 0)
		goto on_error;

	if (git_oidmap_new(&pb->walk_objects) < 0)
		goto on_error;

	git_pool_init(&pb->object_pool, sizeof(struct walk_object));

	pb->repo = repo;
	pb->nr_threads = 1; /* do not spawn any thread by default */

	if (git_hash_ctx_init(&pb->ctx) < 0 ||
		git_zstream_init(&pb->zstream, GIT_ZSTREAM_DEFLATE) < 0 ||
		git_repository_odb(&pb->odb, repo) < 0 ||
		packbuilder_config(pb) < 0)
		goto on_error;

#ifdef GIT_THREADS

	if (git_mutex_init(&pb->cache_mutex) ||
		git_mutex_init(&pb->progress_mutex) ||
		git_cond_init(&pb->progress_cond))
	{
		git_error_set(GIT_ERROR_OS, "failed to initialize packbuilder mutex");
		goto on_error;
	}

#endif

	*out = pb;
	return 0;

on_error:
	git_packbuilder_free(pb);
	return -1;
}