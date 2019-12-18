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
typedef  int /*<<< orphan*/  git_allocator ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_EINVALID ; 
 int /*<<< orphan*/  GIT_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 

int git_win32_crtdbg_init_allocator(git_allocator *allocator)
{
	GIT_UNUSED(allocator);
	git_error_set(GIT_EINVALID, "crtdbg memory allocator not available");
	return -1;
}