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
typedef  int /*<<< orphan*/  sep ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;
typedef  int /*<<< orphan*/  b ;
typedef  int /*<<< orphan*/  a ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_join (TYPE_1__*,char,char*,char*) ; 

void test_core_buffer__9(void)
{
	git_buf buf = GIT_BUF_INIT;

	/* just some exhaustive tests of various separator placement */
	char *a[] = { "", "-", "a-", "-a", "-a-" };
	char *b[] = { "", "-", "b-", "-b", "-b-" };
	char sep[] = { 0, '-', '/' };
	char *expect_null[] = { "",    "-",     "a-",     "-a",     "-a-",
							"-",   "--",    "a--",    "-a-",    "-a--",
							"b-",  "-b-",   "a-b-",   "-ab-",   "-a-b-",
							"-b",  "--b",   "a--b",   "-a-b",   "-a--b",
							"-b-", "--b-",  "a--b-",  "-a-b-",  "-a--b-" };
	char *expect_dash[] = { "",    "-",     "a-",     "-a-",    "-a-",
							"-",   "-",     "a-",     "-a-",    "-a-",
							"b-",  "-b-",   "a-b-",   "-a-b-",  "-a-b-",
							"-b",  "-b",    "a-b",    "-a-b",   "-a-b",
							"-b-", "-b-",   "a-b-",   "-a-b-",  "-a-b-" };
	char *expect_slas[] = { "",    "-/",    "a-/",    "-a/",    "-a-/",
							"-",   "-/-",   "a-/-",   "-a/-",   "-a-/-",
							"b-",  "-/b-",  "a-/b-",  "-a/b-",  "-a-/b-",
							"-b",  "-/-b",  "a-/-b",  "-a/-b",  "-a-/-b",
							"-b-", "-/-b-", "a-/-b-", "-a/-b-", "-a-/-b-" };
	char **expect_values[] = { expect_null, expect_dash, expect_slas };
	char separator, **expect;
	unsigned int s, i, j;

	for (s = 0; s < sizeof(sep) / sizeof(char); ++s) {
		separator = sep[s];
		expect = expect_values[s];

		for (j = 0; j < sizeof(b) / sizeof(char*); ++j) {
			for (i = 0; i < sizeof(a) / sizeof(char*); ++i) {
				git_buf_join(&buf, separator, a[i], b[j]);
				cl_assert_equal_s(*expect, buf.ptr);
				expect++;
			}
		}
	}

	git_buf_dispose(&buf);
}