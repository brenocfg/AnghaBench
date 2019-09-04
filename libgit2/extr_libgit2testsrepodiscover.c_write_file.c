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
typedef  scalar_t__ git_file ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int) ; 
 scalar_t__ git_futils_creat_withpath (char const*,int,int) ; 
 scalar_t__ git_path_exists (char const*) ; 
 int /*<<< orphan*/  p_close (scalar_t__) ; 
 int p_unlink (char const*) ; 
 int p_write (scalar_t__,char const*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void write_file(const char *path, const char *content)
{
	git_file file;
	int error;

	if (git_path_exists(path)) {
		cl_git_pass(p_unlink(path));
	}

	file = git_futils_creat_withpath(path, 0777, 0666);
	cl_assert(file >= 0);

	error = p_write(file, content, strlen(content) * sizeof(char));
	p_close(file);
	cl_git_pass(error);
}