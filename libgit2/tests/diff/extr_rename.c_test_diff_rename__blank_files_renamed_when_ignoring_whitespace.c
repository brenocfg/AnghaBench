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
 int /*<<< orphan*/  GIT_DIFF_FIND_IGNORE_WHITESPACE ; 
 int /*<<< orphan*/  expect_files_renamed (char*,char*,int /*<<< orphan*/ ) ; 

void test_diff_rename__blank_files_renamed_when_ignoring_whitespace(void)
{
	expect_files_renamed("", "\n\n",  GIT_DIFF_FIND_IGNORE_WHITESPACE);
	expect_files_renamed("", "\r\n\r\n",  GIT_DIFF_FIND_IGNORE_WHITESPACE);
	expect_files_renamed("\r\n\r\n", "\n\n\n",  GIT_DIFF_FIND_IGNORE_WHITESPACE);

	expect_files_renamed("    ", "\n\n",  GIT_DIFF_FIND_IGNORE_WHITESPACE);
	expect_files_renamed("   \n   \n", "\n\n",  GIT_DIFF_FIND_IGNORE_WHITESPACE);
}