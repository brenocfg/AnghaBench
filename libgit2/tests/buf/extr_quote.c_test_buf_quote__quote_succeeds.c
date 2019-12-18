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
 int /*<<< orphan*/  expect_quote_pass (char*,char*) ; 

void test_buf_quote__quote_succeeds(void)
{
	expect_quote_pass("", "");
	expect_quote_pass("foo", "foo");
	expect_quote_pass("foo/bar/baz.c", "foo/bar/baz.c");
	expect_quote_pass("foo bar", "foo bar");
	expect_quote_pass("\"\\\"leading quote\"", "\"leading quote");
	expect_quote_pass("\"slash\\\\y\"", "slash\\y");
	expect_quote_pass("\"foo\\r\\nbar\"", "foo\r\nbar");
	expect_quote_pass("\"foo\\177bar\"", "foo\177bar");
	expect_quote_pass("\"foo\\001bar\"", "foo\001bar");
	expect_quote_pass("\"foo\\377bar\"", "foo\377bar");
}