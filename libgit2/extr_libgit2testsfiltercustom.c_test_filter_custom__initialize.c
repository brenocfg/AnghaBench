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
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  register_custom_filters () ; 

void test_filter_custom__initialize(void)
{
	register_custom_filters();

	g_repo = cl_git_sandbox_init("empty_standard_repo");

	cl_git_mkfile(
		"empty_standard_repo/.gitattributes",
		"hero* bitflip reverse\n"
		"herofile text\n"
		"heroflip -reverse binary\n"
		"villain erroneous\n"
		"*.bin binary\n");
}