#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  git_refspec ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git__free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git__malloc (int) ; 
 scalar_t__ git_refspec__parse (int /*<<< orphan*/ *,char const*,int) ; 

int git_refspec_parse(git_refspec **out_refspec, const char *input, int is_fetch)
{
	git_refspec *refspec;
	assert(out_refspec && input);

	*out_refspec = NULL;

	refspec = git__malloc(sizeof(git_refspec));
	GIT_ERROR_CHECK_ALLOC(refspec);

	if (git_refspec__parse(refspec, input, !!is_fetch) != 0) {
		git__free(refspec);
		return -1;
	}

	*out_refspec = refspec;
	return 0;
}