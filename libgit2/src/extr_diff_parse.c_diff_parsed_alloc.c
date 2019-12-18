#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  flags; } ;
struct TYPE_10__ {int /*<<< orphan*/  deltas; int /*<<< orphan*/  pool; TYPE_2__ opts; int /*<<< orphan*/  free_fn; int /*<<< orphan*/  patch_fn; int /*<<< orphan*/  entrycomp; int /*<<< orphan*/  pfxcomp; int /*<<< orphan*/  strncomp; int /*<<< orphan*/  strcomp; int /*<<< orphan*/  type; } ;
struct TYPE_8__ {TYPE_3__ base; int /*<<< orphan*/  patches; } ;
typedef  TYPE_1__ git_diff_parsed ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DIFF_IGNORE_CASE ; 
 int /*<<< orphan*/  GIT_DIFF_OPTIONS_VERSION ; 
 int /*<<< orphan*/  GIT_DIFF_TYPE_PARSED ; 
 int /*<<< orphan*/  GIT_REFCOUNT_INC (TYPE_3__*) ; 
 int /*<<< orphan*/  diff_parsed_free ; 
 TYPE_1__* git__calloc (int,int) ; 
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int /*<<< orphan*/  git__prefixcmp ; 
 int /*<<< orphan*/  git__strcmp ; 
 int /*<<< orphan*/  git__strncmp ; 
 int /*<<< orphan*/  git_diff__entry_cmp ; 
 int /*<<< orphan*/ * git_diff_delta__cmp ; 
 int /*<<< orphan*/  git_diff_free (TYPE_3__*) ; 
 scalar_t__ git_diff_options_init (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_patch_parsed_from_diff ; 
 int /*<<< orphan*/  git_pool_init (int /*<<< orphan*/ *,int) ; 
 scalar_t__ git_vector_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_set_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static git_diff_parsed *diff_parsed_alloc(void)
{
	git_diff_parsed *diff;

	if ((diff = git__calloc(1, sizeof(git_diff_parsed))) == NULL)
		return NULL;

	GIT_REFCOUNT_INC(&diff->base);
	diff->base.type = GIT_DIFF_TYPE_PARSED;
	diff->base.strcomp = git__strcmp;
	diff->base.strncomp = git__strncmp;
	diff->base.pfxcomp = git__prefixcmp;
	diff->base.entrycomp = git_diff__entry_cmp;
	diff->base.patch_fn = git_patch_parsed_from_diff;
	diff->base.free_fn = diff_parsed_free;

	if (git_diff_options_init(&diff->base.opts, GIT_DIFF_OPTIONS_VERSION) < 0) {
		git__free(diff);
		return NULL;
	}

	diff->base.opts.flags &= ~GIT_DIFF_IGNORE_CASE;

	git_pool_init(&diff->base.pool, 1);

	if (git_vector_init(&diff->patches, 0, NULL) < 0 ||
		git_vector_init(&diff->base.deltas, 0, git_diff_delta__cmp) < 0) {
		git_diff_free(&diff->base);
		return NULL;
	}

	git_vector_set_cmp(&diff->base.deltas, git_diff_delta__cmp);

	return diff;
}