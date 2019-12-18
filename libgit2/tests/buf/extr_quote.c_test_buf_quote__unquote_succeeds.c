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
 int /*<<< orphan*/  expect_unquote_pass (char*,char*) ; 

void test_buf_quote__unquote_succeeds(void)
{
	expect_unquote_pass("", "\"\"");
	expect_unquote_pass(" ", "\" \"");
	expect_unquote_pass("foo", "\"foo\"");
	expect_unquote_pass("foo bar", "\"foo bar\"");
	expect_unquote_pass("foo\"bar", "\"foo\\\"bar\"");
	expect_unquote_pass("foo\\bar", "\"foo\\\\bar\"");
	expect_unquote_pass("foo\tbar", "\"foo\\tbar\"");
	expect_unquote_pass("\vfoo\tbar\n", "\"\\vfoo\\tbar\\n\"");
	expect_unquote_pass("foo\nbar", "\"foo\\012bar\"");
	expect_unquote_pass("foo\r\nbar", "\"foo\\015\\012bar\"");
	expect_unquote_pass("foo\r\nbar", "\"\\146\\157\\157\\015\\012\\142\\141\\162\"");
	expect_unquote_pass("newline: \n", "\"newline: \\012\"");
	expect_unquote_pass("0xff: \377", "\"0xff: \\377\"");
}