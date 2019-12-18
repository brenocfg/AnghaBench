#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct compare_data {char* member_0; char const* member_2; char const* member_3; char const* member_4; char* dirname; int /*<<< orphan*/ * member_1; } ;
struct TYPE_10__ {char* ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  add_and_check_file ; 
 int /*<<< orphan*/  cl_fixture_cleanup (char*) ; 
 int /*<<< orphan*/  cl_fixture_sandbox (char*) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_repo_set_string (int /*<<< orphan*/ ,char*,char const*) ; 
 TYPE_1__ expected_fixture ; 
 int /*<<< orphan*/  g_index ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  git_buf_printf (TYPE_1__*,char*,char const*) ; 
 int /*<<< orphan*/  git_buf_putc (TYPE_1__*,char const) ; 
 int /*<<< orphan*/  git_buf_puts (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  git_index_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_direach (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct compare_data*) ; 
 char* system_type () ; 

__attribute__((used)) static void test_add_index(const char *safecrlf, const char *autocrlf, const char *attrs)
{
	git_buf attrbuf = GIT_BUF_INIT;
	git_buf expected_dirname = GIT_BUF_INIT;
	git_buf sandboxname = GIT_BUF_INIT;
	git_buf reponame = GIT_BUF_INIT;
	struct compare_data compare_data = { system_type(), NULL, safecrlf, autocrlf, attrs };
	const char *c;

	git_buf_puts(&reponame, "crlf");

	git_buf_puts(&sandboxname, "autocrlf_");
	git_buf_puts(&sandboxname, autocrlf);

	git_buf_puts(&sandboxname, ",safecrlf_");
	git_buf_puts(&sandboxname, safecrlf);

	if (*attrs) {
		git_buf_puts(&sandboxname, ",");

		for (c = attrs; *c; c++) {
			if (*c == ' ')
				git_buf_putc(&sandboxname, ',');
			else if (*c == '=')
				git_buf_putc(&sandboxname, '_');
			else
				git_buf_putc(&sandboxname, *c);
		}

		git_buf_printf(&attrbuf, "* %s\n", attrs);
		cl_git_mkfile("crlf/.gitattributes", attrbuf.ptr);
	}

	cl_repo_set_string(g_repo, "core.safecrlf", safecrlf);
	cl_repo_set_string(g_repo, "core.autocrlf", autocrlf);

	cl_git_pass(git_index_clear(g_index));

	git_buf_joinpath(&expected_dirname, "crlf_data", system_type());
	git_buf_puts(&expected_dirname, "_to_odb");

	git_buf_joinpath(&expected_fixture, expected_dirname.ptr, sandboxname.ptr);
	cl_fixture_sandbox(expected_fixture.ptr);

	compare_data.dirname = sandboxname.ptr;
	cl_git_pass(git_path_direach(&reponame, 0, add_and_check_file, &compare_data));

	cl_fixture_cleanup(expected_fixture.ptr);
	git_buf_dispose(&expected_fixture);

	git_buf_dispose(&attrbuf);
	git_buf_dispose(&expected_fixture);
	git_buf_dispose(&expected_dirname);
	git_buf_dispose(&sandboxname);
	git_buf_dispose(&reponame);
}