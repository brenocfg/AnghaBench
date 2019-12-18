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
struct TYPE_2__ {int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISCOVER_FOLDER ; 
 int /*<<< orphan*/  SUB_REPOSITORY_FOLDER ; 
 TYPE_1__ ceiling_dirs ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  discovered ; 
 int /*<<< orphan*/  git_repository_discover (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void test_repo_discover__discovering_repo_with_exact_path_succeeds(void)
{
	cl_git_pass(git_repository_discover(&discovered, DISCOVER_FOLDER, 0, ceiling_dirs.ptr));
	cl_git_pass(git_repository_discover(&discovered, SUB_REPOSITORY_FOLDER, 0, ceiling_dirs.ptr));
}