#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ git_hashsig_option_t ;
typedef  int /*<<< orphan*/  git_hashsig ;
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 scalar_t__ GIT_HASHSIG_NORMAL ; 
 scalar_t__ GIT_HASHSIG_SMART_WHITESPACE ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_assert_in_range (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_sets (TYPE_1__*,char const*) ; 
 int git_hashsig_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_hashsig_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  git_hashsig_free (int /*<<< orphan*/ *) ; 

void test_core_buffer__similarity_metric_whitespace(void)
{
	git_hashsig *a, *b;
	git_buf buf = GIT_BUF_INIT;
	int sim, i, j;
	git_hashsig_option_t opt;
	const char *tabbed =
		"	for (s = 0; s < sizeof(sep) / sizeof(char); ++s) {\n"
		"		separator = sep[s];\n"
		"		expect = expect_values[s];\n"
		"\n"
		"		for (j = 0; j < sizeof(b) / sizeof(char*); ++j) {\n"
		"			for (i = 0; i < sizeof(a) / sizeof(char*); ++i) {\n"
		"				git_buf_join(&buf, separator, a[i], b[j]);\n"
		"				cl_assert_equal_s(*expect, buf.ptr);\n"
		"				expect++;\n"
		"			}\n"
		"		}\n"
		"	}\n";
	const char *spaced =
		"   for (s = 0; s < sizeof(sep) / sizeof(char); ++s) {\n"
		"       separator = sep[s];\n"
		"       expect = expect_values[s];\n"
		"\n"
		"       for (j = 0; j < sizeof(b) / sizeof(char*); ++j) {\n"
		"           for (i = 0; i < sizeof(a) / sizeof(char*); ++i) {\n"
		"               git_buf_join(&buf, separator, a[i], b[j]);\n"
		"               cl_assert_equal_s(*expect, buf.ptr);\n"
		"               expect++;\n"
		"           }\n"
		"       }\n"
		"   }\n";
	const char *crlf_spaced2 =
		"  for (s = 0; s < sizeof(sep) / sizeof(char); ++s) {\r\n"
		"    separator = sep[s];\r\n"
		"    expect = expect_values[s];\r\n"
		"\r\n"
		"    for (j = 0; j < sizeof(b) / sizeof(char*); ++j) {\r\n"
		"      for (i = 0; i < sizeof(a) / sizeof(char*); ++i) {\r\n"
		"        git_buf_join(&buf, separator, a[i], b[j]);\r\n"
		"        cl_assert_equal_s(*expect, buf.ptr);\r\n"
		"        expect++;\r\n"
		"      }\r\n"
		"    }\r\n"
		"  }\r\n";
	const char *text[3] = { tabbed, spaced, crlf_spaced2 };

	/* let's try variations of our own code with whitespace changes */

	for (opt = GIT_HASHSIG_NORMAL; opt <= GIT_HASHSIG_SMART_WHITESPACE; ++opt) {
		for (i = 0; i < 3; ++i) {
			for (j = 0; j < 3; ++j) {
				cl_git_pass(git_buf_sets(&buf, text[i]));
				cl_git_pass(git_hashsig_create(&a, buf.ptr, buf.size, opt));

				cl_git_pass(git_buf_sets(&buf, text[j]));
				cl_git_pass(git_hashsig_create(&b, buf.ptr, buf.size, opt));

				sim = git_hashsig_compare(a, b);

				if (opt == GIT_HASHSIG_NORMAL) {
					if (i == j)
						cl_assert_equal_i(100, sim);
					else
						cl_assert_in_range(0, sim, 30); /* pretty different */
				} else {
					cl_assert_equal_i(100, sim);
				}

				git_hashsig_free(a);
				git_hashsig_free(b);
			}
		}
	}

	git_buf_dispose(&buf);
}