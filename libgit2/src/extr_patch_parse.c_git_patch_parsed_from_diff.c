#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_patch ;
struct TYPE_2__ {int /*<<< orphan*/  patches; } ;
typedef  TYPE_1__ git_diff_parsed ;
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_REFCOUNT_INC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_vector_get (int /*<<< orphan*/ *,size_t) ; 

int git_patch_parsed_from_diff(git_patch **out, git_diff *d, size_t idx)
{
	git_diff_parsed *diff = (git_diff_parsed *)d;
	git_patch *p;

	if ((p = git_vector_get(&diff->patches, idx)) == NULL)
		return -1;

	GIT_REFCOUNT_INC(p);
	*out = p;

	return 0;
}