#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int count; int /*<<< orphan*/ * strings; } ;
typedef  TYPE_1__ git_strarray ;
struct TYPE_6__ {int /*<<< orphan*/  worktree; int /*<<< orphan*/  repo; } ;

/* Variables and functions */
 int GIT_ERROR ; 
 int /*<<< orphan*/  cl_git_pass (int) ; 
 TYPE_4__ fixture ; 
 int git_reference_list (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_strarray_free (TYPE_1__*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void test_worktree_refs__list(void)
{
	git_strarray refs, wtrefs;
	unsigned i, j;
	int error = 0;

	cl_git_pass(git_reference_list(&refs, fixture.repo));
	cl_git_pass(git_reference_list(&wtrefs, fixture.worktree));

	if (refs.count != wtrefs.count)
	{
		error = GIT_ERROR;
		goto exit;
	}

	for (i = 0; i < refs.count; i++)
	{
		int found = 0;

		for (j = 0; j < wtrefs.count; j++)
		{
			if (!strcmp(refs.strings[i], wtrefs.strings[j]))
			{
				found = 1;
				break;
			}
		}

		if (!found)
		{
			error = GIT_ERROR;
			goto exit;
		}
	}

exit:
	git_strarray_free(&refs);
	git_strarray_free(&wtrefs);
	cl_git_pass(error);
}