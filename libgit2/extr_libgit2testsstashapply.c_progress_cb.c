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
typedef  scalar_t__ git_stash_apply_progress_t ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_i (scalar_t__,scalar_t__) ; 

int progress_cb(
	git_stash_apply_progress_t progress,
	void *payload)
{
	git_stash_apply_progress_t *p = (git_stash_apply_progress_t *)payload;

	cl_assert_equal_i((*p)+1, progress);

	*p = progress;

	return 0;
}