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
 int /*<<< orphan*/  expect_unquote_fail (char*) ; 

void test_buf_quote__unquote_fails(void)
{
	expect_unquote_fail("no quotes at all");
	expect_unquote_fail("\"no trailing quote");
	expect_unquote_fail("no leading quote\"");
	expect_unquote_fail("\"invalid \\z escape char\"");
	expect_unquote_fail("\"\\q invalid escape char\"");
	expect_unquote_fail("\"invalid escape char \\p\"");
	expect_unquote_fail("\"invalid \\1 escape char \"");
	expect_unquote_fail("\"invalid \\14 escape char \"");
	expect_unquote_fail("\"invalid \\280 escape char\"");
	expect_unquote_fail("\"invalid \\378 escape char\"");
	expect_unquote_fail("\"invalid \\380 escape char\"");
	expect_unquote_fail("\"invalid \\411 escape char\"");
	expect_unquote_fail("\"truncated escape char \\\"");
	expect_unquote_fail("\"truncated escape char \\0\"");
	expect_unquote_fail("\"truncated escape char \\01\"");
}