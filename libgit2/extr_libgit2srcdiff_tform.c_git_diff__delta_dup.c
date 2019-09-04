#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_pool ;
struct TYPE_11__ {int /*<<< orphan*/ * path; } ;
struct TYPE_10__ {int /*<<< orphan*/ * path; } ;
struct TYPE_12__ {TYPE_2__ old_file; TYPE_1__ new_file; int /*<<< orphan*/  flags; } ;
typedef  TYPE_3__ git_diff_delta ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DIFF_FLAG__CLEAR_INTERNAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git__free (TYPE_3__*) ; 
 TYPE_3__* git__malloc (int) ; 
 void* git_pool_strdup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_3__ const*,int) ; 

git_diff_delta *git_diff__delta_dup(
	const git_diff_delta *d, git_pool *pool)
{
	git_diff_delta *delta = git__malloc(sizeof(git_diff_delta));
	if (!delta)
		return NULL;

	memcpy(delta, d, sizeof(git_diff_delta));
	GIT_DIFF_FLAG__CLEAR_INTERNAL(delta->flags);

	if (d->old_file.path != NULL) {
		delta->old_file.path = git_pool_strdup(pool, d->old_file.path);
		if (delta->old_file.path == NULL)
			goto fail;
	}

	if (d->new_file.path != d->old_file.path && d->new_file.path != NULL) {
		delta->new_file.path = git_pool_strdup(pool, d->new_file.path);
		if (delta->new_file.path == NULL)
			goto fail;
	} else {
		delta->new_file.path = delta->old_file.path;
	}

	return delta;

fail:
	git__free(delta);
	return NULL;
}