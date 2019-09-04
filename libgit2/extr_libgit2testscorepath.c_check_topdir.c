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
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,char const*) ; 
 char* git_path_topdir (char const*) ; 

__attribute__((used)) static void
check_topdir(const char *A, const char *B)
{
	const char *dir;

	cl_assert((dir = git_path_topdir(A)) != NULL);
	cl_assert_equal_s(B, dir);
}