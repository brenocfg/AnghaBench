#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  zstream; int /*<<< orphan*/  ctx; int /*<<< orphan*/  object_pool; scalar_t__ walk_objects; struct TYPE_4__* object_list; scalar_t__ object_ix; scalar_t__ odb; int /*<<< orphan*/  progress_cond; int /*<<< orphan*/  progress_mutex; int /*<<< orphan*/  cache_mutex; } ;
typedef  TYPE_1__ git_packbuilder ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_cond_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_hash_ctx_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_mutex_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_free (scalar_t__) ; 
 int /*<<< orphan*/  git_oidmap_free (scalar_t__) ; 
 int /*<<< orphan*/  git_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_zstream_free (int /*<<< orphan*/ *) ; 

void git_packbuilder_free(git_packbuilder *pb)
{
	if (pb == NULL)
		return;

#ifdef GIT_THREADS

	git_mutex_free(&pb->cache_mutex);
	git_mutex_free(&pb->progress_mutex);
	git_cond_free(&pb->progress_cond);

#endif

	if (pb->odb)
		git_odb_free(pb->odb);

	if (pb->object_ix)
		git_oidmap_free(pb->object_ix);

	if (pb->object_list)
		git__free(pb->object_list);

	git_oidmap_free(pb->walk_objects);
	git_pool_clear(&pb->object_pool);

	git_hash_ctx_cleanup(&pb->ctx);
	git_zstream_free(&pb->zstream);

	git__free(pb);
}