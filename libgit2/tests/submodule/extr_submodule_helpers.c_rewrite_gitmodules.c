#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  line ;
struct TYPE_9__ {char const* ptr; } ;
typedef  TYPE_1__ git_buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  F_OK ; 
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ git__prefixcmp (char*,char*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,char const*,char*) ; 
 int /*<<< orphan*/  git_buf_oom (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_putc (TYPE_1__*,char) ; 
 int /*<<< orphan*/  git_buf_rtrim (TYPE_1__*) ; 
 int /*<<< orphan*/  git_path_prettify (TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ p_access (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_rename (char const*,char const*) ; 
 int /*<<< orphan*/  p_unlink (char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

void rewrite_gitmodules(const char *workdir)
{
	git_buf in_f = GIT_BUF_INIT, out_f = GIT_BUF_INIT, path = GIT_BUF_INIT;
	FILE *in, *out;
	char line[256];

	cl_git_pass(git_buf_joinpath(&in_f, workdir, "gitmodules"));
	cl_git_pass(git_buf_joinpath(&out_f, workdir, ".gitmodules"));

	cl_assert((in  = fopen(in_f.ptr, "rb")) != NULL);
	cl_assert((out = fopen(out_f.ptr, "wb")) != NULL);

	while (fgets(line, sizeof(line), in) != NULL) {
		char *scan = line;

		while (*scan == ' ' || *scan == '\t') scan++;

		/* rename .gitted -> .git in submodule directories */
		if (git__prefixcmp(scan, "path =") == 0) {
			scan += strlen("path =");
			while (*scan == ' ') scan++;

			git_buf_joinpath(&path, workdir, scan);
			git_buf_rtrim(&path);
			git_buf_joinpath(&path, path.ptr, ".gitted");

			if (!git_buf_oom(&path) && p_access(path.ptr, F_OK) == 0) {
				git_buf_joinpath(&out_f, workdir, scan);
				git_buf_rtrim(&out_f);
				git_buf_joinpath(&out_f, out_f.ptr, ".git");

				if (!git_buf_oom(&out_f))
					p_rename(path.ptr, out_f.ptr);
			}
		}

		/* copy non-"url =" lines verbatim */
		if (git__prefixcmp(scan, "url =") != 0) {
			fputs(line, out);
			continue;
		}

		/* convert relative URLs in "url =" lines */
		scan += strlen("url =");
		while (*scan == ' ') scan++;

		if (*scan == '.') {
			git_buf_joinpath(&path, workdir, scan);
			git_buf_rtrim(&path);
		} else if (!*scan || *scan == '\n') {
			git_buf_joinpath(&path, workdir, "../testrepo.git");
		} else {
			fputs(line, out);
			continue;
		}

		git_path_prettify(&path, path.ptr, NULL);
		git_buf_putc(&path, '\n');
		cl_assert(!git_buf_oom(&path));

		fwrite(line, scan - line, sizeof(char), out);
		fputs(path.ptr, out);
	}

	fclose(in);
	fclose(out);

	cl_must_pass(p_unlink(in_f.ptr));

	git_buf_dispose(&in_f);
	git_buf_dispose(&out_f);
	git_buf_dispose(&path);
}