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
struct stat {int st_nlink; } ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int git_path_isfile (char const*) ; 
 int /*<<< orphan*/  p_stat (char const*,struct stat*) ; 

void assert_hard_link(const char *path)
{
	/* we assert this by checking that there's more than one link to the file */
	struct stat st;

	cl_assert(git_path_isfile(path));
	cl_git_pass(p_stat(path, &st));
	cl_assert(st.st_nlink > 1);
}