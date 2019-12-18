#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_5__ {scalar_t__ type; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ git_reference ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_HEAD_FILE ; 
 scalar_t__ GIT_REFERENCE_DIRECT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ git__strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (TYPE_1__*) ; 
 int git_reference_lookup_resolved (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int git_reference__is_unborn_head(bool *unborn, const git_reference *ref, git_repository *repo)
{
	int error;
	git_reference *tmp_ref;
	assert(unborn && ref && repo);

	if (ref->type == GIT_REFERENCE_DIRECT) {
		*unborn = 0;
		return 0;
	}

	error = git_reference_lookup_resolved(&tmp_ref, repo, ref->name, -1);
	git_reference_free(tmp_ref);

	if (error != 0 && error != GIT_ENOTFOUND)
		return error;
	else if (error == GIT_ENOTFOUND && git__strcmp(ref->name, GIT_HEAD_FILE) == 0)
		*unborn = true;
	else
		*unborn = false;

	return 0;
}