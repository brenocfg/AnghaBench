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
typedef  void git_diff ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (void*) ; 

__attribute__((used)) static int progress_abort_diff(
	const git_diff *diff_so_far,
	const char *old_path,
	const char *new_path,
	void *payload)
{
	GIT_UNUSED(diff_so_far);
	GIT_UNUSED(old_path);
	GIT_UNUSED(new_path);
	GIT_UNUSED(payload);

	return -42;
}