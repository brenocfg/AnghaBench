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
 scalar_t__ GIT_STASH_APPLY_PROGRESS_ANALYZE_MODIFIED ; 
 int /*<<< orphan*/  GIT_UNUSED (void*) ; 

int aborting_progress_cb(
	git_stash_apply_progress_t progress,
	void *payload)
{
	GIT_UNUSED(payload);

	if (progress == GIT_STASH_APPLY_PROGRESS_ANALYZE_MODIFIED)
		return -44;

	return 0;
}