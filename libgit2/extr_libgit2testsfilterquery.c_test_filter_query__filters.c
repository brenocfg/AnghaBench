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
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter_for (char*,char*) ; 

void test_filter_query__filters(void)
{
	cl_assert_equal_i(1, filter_for("text.txt", "crlf"));
	cl_assert_equal_i(0, filter_for("binary.bin", "crlf"));

	cl_assert_equal_i(1, filter_for("foo.lf", "crlf"));
	cl_assert_equal_i(0, filter_for("foo.lf", "ident"));

	cl_assert_equal_i(1, filter_for("id.ident", "crlf"));
	cl_assert_equal_i(1, filter_for("id.ident", "ident"));

	cl_assert_equal_i(0, filter_for("id.binident", "crlf"));
	cl_assert_equal_i(1, filter_for("id.binident", "ident"));
}