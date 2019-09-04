#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  names; } ;
typedef  TYPE_1__ walk_data ;
typedef  int /*<<< orphan*/  git_path_diriter ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_s (char const*,char const*) ; 
 int /*<<< orphan*/  cl_assert_equal_strn (char const*,char*,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_diriter_filename (char const**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_path_diriter_fullpath (char const**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_count (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void handle_next(git_path_diriter *diriter, walk_data *walk)
{
	const char *fullpath, *filename;
	size_t fullpath_len, filename_len;

	cl_git_pass(git_path_diriter_fullpath(&fullpath, &fullpath_len, diriter));
	cl_git_pass(git_path_diriter_filename(&filename, &filename_len, diriter));

	cl_assert_equal_strn(fullpath, "sub/", 4);
	cl_assert_equal_s(fullpath+4, filename);

	update_count(walk->names, fullpath);
}