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
typedef  scalar_t__ git_sysdir_t ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_sysdir__dirs ; 

__attribute__((used)) static int git_sysdir_check_selector(git_sysdir_t which)
{
	if (which < ARRAY_SIZE(git_sysdir__dirs))
		return 0;

	git_error_set(GIT_ERROR_INVALID, "config directory selector out of range");
	return -1;
}