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
 int /*<<< orphan*/  assert_is_ignored (int,char*) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 

void test_ignore_path__leading_stars(void)
{
	cl_git_rewritefile(
		"attr/.gitignore",
		"*/onestar\n"
		"**/twostars\n"
		"*/parent1/kid1/*\n"
		"**/parent2/kid2/*\n");

	assert_is_ignored(true, "dir1/onestar");
	assert_is_ignored(true, "dir1/onestar/child"); /* in ignored dir */
	assert_is_ignored(false, "dir1/dir2/onestar");

	assert_is_ignored(true, "dir1/twostars");
	assert_is_ignored(true, "dir1/twostars/child"); /* in ignored dir */
	assert_is_ignored(true, "dir1/dir2/twostars");
	assert_is_ignored(true, "dir1/dir2/twostars/child"); /* in ignored dir */
	assert_is_ignored(true, "dir1/dir2/dir3/twostars");

	assert_is_ignored(true, "dir1/parent1/kid1/file");
	assert_is_ignored(true, "dir1/parent1/kid1/file/inside/parent");
	assert_is_ignored(false, "dir1/dir2/parent1/kid1/file");
	assert_is_ignored(false, "dir1/parent1/file");
	assert_is_ignored(false, "dir1/kid1/file");

	assert_is_ignored(true, "dir1/parent2/kid2/file");
	assert_is_ignored(true, "dir1/parent2/kid2/file/inside/parent");
	assert_is_ignored(true, "dir1/dir2/parent2/kid2/file");
	assert_is_ignored(true, "dir1/dir2/dir3/parent2/kid2/file");
	assert_is_ignored(false, "dir1/parent2/file");
	assert_is_ignored(false, "dir1/kid2/file");
}