#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int size; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 char* git_buf_cstr (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_putc (TYPE_1__*,char const) ; 
 int /*<<< orphan*/  git_buf_puts (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  git_path_prettify_dir (TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

const char* cl_git_path_url(const char *path)
{
	static char url[4096];

	const char *in_buf;
	git_buf path_buf = GIT_BUF_INIT;
	git_buf url_buf = GIT_BUF_INIT;

	cl_git_pass(git_path_prettify_dir(&path_buf, path, NULL));
	cl_git_pass(git_buf_puts(&url_buf, "file://"));

#ifdef GIT_WIN32
	/*
	 * A FILE uri matches the following format: file://[host]/path
	 * where "host" can be empty and "path" is an absolute path to the resource.
	 *
	 * In this test, no hostname is used, but we have to ensure the leading triple slashes:
	 *
	 * *nix: file:///usr/home/...
	 * Windows: file:///C:/Users/...
	 */
	cl_git_pass(git_buf_putc(&url_buf, '/'));
#endif

	in_buf = git_buf_cstr(&path_buf);

	/*
	 * A very hacky Url encoding that only takes care of escaping the spaces
	 */
	while (*in_buf) {
		if (*in_buf == ' ')
			cl_git_pass(git_buf_puts(&url_buf, "%20"));
		else
			cl_git_pass(git_buf_putc(&url_buf, *in_buf));

		in_buf++;
	}

	cl_assert(url_buf.size < 4096);

	strncpy(url, git_buf_cstr(&url_buf), 4096);
	git_buf_dispose(&url_buf);
	git_buf_dispose(&path_buf);
	return url;
}