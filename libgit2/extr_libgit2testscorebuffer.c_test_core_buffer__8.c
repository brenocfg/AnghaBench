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
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  check_joinbuf_2 (char*,char*,char*) ; 
 int /*<<< orphan*/  check_joinbuf_n_2 (char*,char*,char*) ; 
 int /*<<< orphan*/  check_joinbuf_n_4 (char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  check_joinbuf_overlapped (char*,int,char*,char*) ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_join_n (int /*<<< orphan*/ *,char,int,char*) ; 
 scalar_t__ git_buf_oom (int /*<<< orphan*/ *) ; 

void test_core_buffer__8(void)
{
	git_buf a = GIT_BUF_INIT;

	git_buf_join_n(&a, '/', 1, "foo");
	cl_assert(git_buf_oom(&a) == 0);
	cl_assert_equal_s("foo", git_buf_cstr(&a));

	git_buf_join_n(&a, '/', 1, "bar");
	cl_assert(git_buf_oom(&a) == 0);
	cl_assert_equal_s("foo/bar", git_buf_cstr(&a));

	git_buf_join_n(&a, '/', 1, "baz");
	cl_assert(git_buf_oom(&a) == 0);
	cl_assert_equal_s("foo/bar/baz", git_buf_cstr(&a));

	git_buf_dispose(&a);

	check_joinbuf_2(NULL, "", "");
	check_joinbuf_2(NULL, "a", "a");
	check_joinbuf_2(NULL, "/a", "/a");
	check_joinbuf_2("", "", "");
	check_joinbuf_2("", "a", "a");
	check_joinbuf_2("", "/a", "/a");
	check_joinbuf_2("a", "", "a/");
	check_joinbuf_2("a", "/", "a/");
	check_joinbuf_2("a", "b", "a/b");
	check_joinbuf_2("/", "a", "/a");
	check_joinbuf_2("/", "", "/");
	check_joinbuf_2("/a", "/b", "/a/b");
	check_joinbuf_2("/a", "/b/", "/a/b/");
	check_joinbuf_2("/a/", "b/", "/a/b/");
	check_joinbuf_2("/a/", "/b/", "/a/b/");
	check_joinbuf_2("/a/", "//b/", "/a/b/");
	check_joinbuf_2("/abcd", "/defg", "/abcd/defg");
	check_joinbuf_2("/abcd", "/defg/", "/abcd/defg/");
	check_joinbuf_2("/abcd/", "defg/", "/abcd/defg/");
	check_joinbuf_2("/abcd/", "/defg/", "/abcd/defg/");

	check_joinbuf_overlapped("abcd", 0, "efg", "abcd/efg");
	check_joinbuf_overlapped("abcd", 1, "efg", "bcd/efg");
	check_joinbuf_overlapped("abcd", 2, "efg", "cd/efg");
	check_joinbuf_overlapped("abcd", 3, "efg", "d/efg");
	check_joinbuf_overlapped("abcd", 4, "efg", "efg");
	check_joinbuf_overlapped("abc/", 2, "efg", "c/efg");
	check_joinbuf_overlapped("abc/", 3, "efg", "/efg");
	check_joinbuf_overlapped("abc/", 4, "efg", "efg");
	check_joinbuf_overlapped("abcd", 3, "", "d/");
	check_joinbuf_overlapped("abcd", 4, "", "");
	check_joinbuf_overlapped("abc/", 2, "", "c/");
	check_joinbuf_overlapped("abc/", 3, "", "/");
	check_joinbuf_overlapped("abc/", 4, "", "");

	check_joinbuf_n_2("", "", "");
	check_joinbuf_n_2("", "a", "a");
	check_joinbuf_n_2("", "/a", "/a");
	check_joinbuf_n_2("a", "", "a/");
	check_joinbuf_n_2("a", "/", "a/");
	check_joinbuf_n_2("a", "b", "a/b");
	check_joinbuf_n_2("/", "a", "/a");
	check_joinbuf_n_2("/", "", "/");
	check_joinbuf_n_2("/a", "/b", "/a/b");
	check_joinbuf_n_2("/a", "/b/", "/a/b/");
	check_joinbuf_n_2("/a/", "b/", "/a/b/");
	check_joinbuf_n_2("/a/", "/b/", "/a/b/");
	check_joinbuf_n_2("/abcd", "/defg", "/abcd/defg");
	check_joinbuf_n_2("/abcd", "/defg/", "/abcd/defg/");
	check_joinbuf_n_2("/abcd/", "defg/", "/abcd/defg/");
	check_joinbuf_n_2("/abcd/", "/defg/", "/abcd/defg/");

	check_joinbuf_n_4("", "", "", "", "");
	check_joinbuf_n_4("", "a", "", "", "a;");
	check_joinbuf_n_4("a", "", "", "", "a;");
	check_joinbuf_n_4("", "", "", "a", "a");
	check_joinbuf_n_4("a", "b", "", ";c;d;", "a;b;c;d;");
	check_joinbuf_n_4("a", "b", "", ";c;d", "a;b;c;d");
	check_joinbuf_n_4("abcd", "efgh", "ijkl", "mnop", "abcd;efgh;ijkl;mnop");
	check_joinbuf_n_4("abcd;", "efgh;", "ijkl;", "mnop;", "abcd;efgh;ijkl;mnop;");
	check_joinbuf_n_4(";abcd;", ";efgh;", ";ijkl;", ";mnop;", ";abcd;efgh;ijkl;mnop;");
}