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

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_TREE ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*,...) ; 

__attribute__((used)) static int tree_error(const char *str, const char *path)
{
	if (path)
		git_error_set(GIT_ERROR_TREE, "%s - %s", str, path);
	else
		git_error_set(GIT_ERROR_TREE, "%s", str);
	return -1;
}