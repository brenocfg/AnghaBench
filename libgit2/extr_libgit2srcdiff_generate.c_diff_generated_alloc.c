#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_11__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ git_iterator ;
typedef  int /*<<< orphan*/  git_diff_options ;
struct TYPE_13__ {int /*<<< orphan*/  deltas; int /*<<< orphan*/  pool; int /*<<< orphan*/  opts; int /*<<< orphan*/  attrsession; int /*<<< orphan*/  free_fn; int /*<<< orphan*/  patch_fn; int /*<<< orphan*/  new_src; int /*<<< orphan*/  old_src; int /*<<< orphan*/ * repo; int /*<<< orphan*/  type; } ;
struct TYPE_12__ {TYPE_4__ base; } ;
typedef  TYPE_2__ git_diff_generated ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DIFF_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_DIFF_TYPE_GENERATED ; 
 int /*<<< orphan*/  GIT_REFCOUNT_INC (TYPE_4__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diff_generated_free ; 
 TYPE_2__* git__calloc (int,int) ; 
 int /*<<< orphan*/  git_attr_session__init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff__set_ignore_case (TYPE_4__*,int) ; 
 int /*<<< orphan*/  git_diff_delta__cmp ; 
 int /*<<< orphan*/  git_diff_free (TYPE_4__*) ; 
 scalar_t__ git_iterator_ignore_case (TYPE_1__*) ; 
 int /*<<< orphan*/  git_patch_generated_from_diff ; 
 int /*<<< orphan*/  git_pool_init (int /*<<< orphan*/ *,int) ; 
 scalar_t__ git_vector_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static git_diff_generated *diff_generated_alloc(
	git_repository *repo,
	git_iterator *old_iter,
	git_iterator *new_iter)
{
	git_diff_generated *diff;
	git_diff_options dflt = GIT_DIFF_OPTIONS_INIT;

	assert(repo && old_iter && new_iter);

	if ((diff = git__calloc(1, sizeof(git_diff_generated))) == NULL)
		return NULL;

	GIT_REFCOUNT_INC(&diff->base);
	diff->base.type = GIT_DIFF_TYPE_GENERATED;
	diff->base.repo = repo;
	diff->base.old_src = old_iter->type;
	diff->base.new_src = new_iter->type;
	diff->base.patch_fn = git_patch_generated_from_diff;
	diff->base.free_fn = diff_generated_free;
	git_attr_session__init(&diff->base.attrsession, repo);
	memcpy(&diff->base.opts, &dflt, sizeof(git_diff_options));

	git_pool_init(&diff->base.pool, 1);

	if (git_vector_init(&diff->base.deltas, 0, git_diff_delta__cmp) < 0) {
		git_diff_free(&diff->base);
		return NULL;
	}

	/* Use case-insensitive compare if either iterator has
	 * the ignore_case bit set */
	git_diff__set_ignore_case(
		&diff->base,
		git_iterator_ignore_case(old_iter) ||
		git_iterator_ignore_case(new_iter));

	return diff;
}