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
struct TYPE_7__ {int /*<<< orphan*/  base; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_patch_generated ;
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 int /*<<< orphan*/  GIT_PATCH_GENERATED_ALLOCATED ; 
 int /*<<< orphan*/  GIT_REFCOUNT_INC (int /*<<< orphan*/ *) ; 
 TYPE_1__* git__calloc (int,int) ; 
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int patch_generated_init (TYPE_1__*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int patch_generated_alloc_from_diff(
	git_patch_generated **out, git_diff *diff, size_t delta_index)
{
	int error;
	git_patch_generated *patch = git__calloc(1, sizeof(git_patch_generated));
	GIT_ERROR_CHECK_ALLOC(patch);

	if (!(error = patch_generated_init(patch, diff, delta_index))) {
		patch->flags |= GIT_PATCH_GENERATED_ALLOCATED;
		GIT_REFCOUNT_INC(&patch->base);
	} else {
		git__free(patch);
		patch = NULL;
	}

	*out = patch;
	return error;
}