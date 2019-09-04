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
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  repo_index ; 
 int /*<<< orphan*/  write_files (char**) ; 

__attribute__((used)) static void stage_random_files(char *files[])
{
	char *filename;
	size_t i;

	write_files(files);

	for (i = 0, filename = files[i]; filename; filename = files[++i])
		cl_git_pass(git_index_add_bypath(repo_index, filename));
}