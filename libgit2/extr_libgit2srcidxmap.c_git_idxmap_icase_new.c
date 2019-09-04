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
typedef  int /*<<< orphan*/  git_idxmap_icase ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idxicase ; 
 int /*<<< orphan*/ * kh_init (int /*<<< orphan*/ ) ; 

int git_idxmap_icase_new(git_idxmap_icase **out)
{
	*out = kh_init(idxicase);
	GIT_ERROR_CHECK_ALLOC(*out);

	return 0;
}