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
 int /*<<< orphan*/  cl_git_expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  clar__assert_equal (char const*,int,char*,int,char*,int,int) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_ignore_path_is_ignored (int*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void assert_is_ignored_(
	bool expected, const char *filepath, const char *file, int line)
{
	int is_ignored = 0;

	cl_git_expect(
		git_ignore_path_is_ignored(&is_ignored, g_repo, filepath), 0, file, line);

	clar__assert_equal(
		file, line, "expected != is_ignored", 1, "%d",
		(int)(expected != 0), (int)(is_ignored != 0));
}