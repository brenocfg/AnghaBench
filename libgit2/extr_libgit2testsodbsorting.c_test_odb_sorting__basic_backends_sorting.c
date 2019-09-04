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
 int /*<<< orphan*/  _odb ; 
 int /*<<< orphan*/  check_backend_sorting (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_odb_add_backend (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  new_backend (int) ; 

void test_odb_sorting__basic_backends_sorting(void)
{
	cl_git_pass(git_odb_add_backend(_odb, new_backend(0), 5));
	cl_git_pass(git_odb_add_backend(_odb, new_backend(2), 3));
	cl_git_pass(git_odb_add_backend(_odb, new_backend(1), 4));
	cl_git_pass(git_odb_add_backend(_odb, new_backend(3), 1));

	check_backend_sorting(_odb);
}