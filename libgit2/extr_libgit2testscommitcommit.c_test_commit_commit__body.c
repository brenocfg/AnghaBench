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
 int /*<<< orphan*/  assert_commit_body (char*,char*) ; 

void test_commit_commit__body(void)
{
	assert_commit_body(NULL, "One-liner with no trailing newline");
	assert_commit_body(NULL, "One-liner with trailing newline\n");
	assert_commit_body(NULL, "\n\nTrimmed leading&trailing newlines\n\n");
	assert_commit_body("(There are more!)", "\nFirst paragraph only\n\n(There are more!)");
	assert_commit_body("(Yes, unwrapped!)", "\nFirst paragraph\nwith  unwrapped\ntrailing\tlines\n\n(Yes, unwrapped!)");
	assert_commit_body("are preserved", "\tLeading\n\ttabs\n\nare preserved"); /* tabs around newlines are collapsed down to a single space */
	assert_commit_body("are preserved", " Leading\n Spaces\n\nare preserved"); /* spaces around newlines are collapsed down to a single space */
	assert_commit_body(NULL, "Trailing tabs\tare removed\t\t");
	assert_commit_body(NULL, "Trailing spaces  are removed  ");
	assert_commit_body("are removed", "Trailing tabs\t\n\nare removed");
	assert_commit_body("are removed", "Trailing spaces \n\nare removed");
	assert_commit_body(NULL,"Newlines\nare\nreplaced by spaces\n");
	assert_commit_body(NULL , "\n  Spaces after newlines\n  are\n  collapsed\n  "); /* newlines at the very beginning are ignored and not collapsed */
	assert_commit_body(NULL , "  \nSpaces before newlines  \nare  \ncollapsed  \n");
	assert_commit_body(NULL , "  \n  Spaces around newlines  \n  are  \n  collapsed  \n  ");
	assert_commit_body("collapsed" , "  \n  Trailing newlines  \n  are  \n\n  collapsed  \n  ");
	assert_commit_body(NULL, "  \n  Trailing spaces \n  are stripped \n\n  \n \t ");
	assert_commit_body(NULL , "");
	assert_commit_body(NULL , " ");
	assert_commit_body(NULL , "\n");
	assert_commit_body(NULL , "\n \n");
}