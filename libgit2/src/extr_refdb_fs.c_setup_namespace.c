#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * namespace; } ;
typedef  TYPE_1__ git_repository ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_MKDIR_PATH ; 
 int /*<<< orphan*/  git__free (char*) ; 
 char* git__strdup (int /*<<< orphan*/ *) ; 
 char* git__strsep (char**,char*) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 char* git_buf_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_printf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  git_buf_puts (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_buf_rtruncate_at_char (int /*<<< orphan*/ *,char) ; 
 scalar_t__ git_futils_mkdir_relative (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *setup_namespace(git_repository *repo, const char *in)
{
	git_buf path = GIT_BUF_INIT;
	char *parts, *start, *end, *out = NULL;

	if (!in)
		goto done;

	git_buf_puts(&path, in);

	/* if the repo is not namespaced, nothing else to do */
	if (repo->namespace == NULL) {
		out = git_buf_detach(&path);
		goto done;
	}

	parts = end = git__strdup(repo->namespace);
	if (parts == NULL)
		goto done;

	/*
	 * From `man gitnamespaces`:
	 *  namespaces which include a / will expand to a hierarchy
	 *  of namespaces; for example, GIT_NAMESPACE=foo/bar will store
	 *  refs under refs/namespaces/foo/refs/namespaces/bar/
	 */
	while ((start = git__strsep(&end, "/")) != NULL)
		git_buf_printf(&path, "refs/namespaces/%s/", start);

	git_buf_printf(&path, "refs/namespaces/%s/refs", end);
	git__free(parts);

	/* Make sure that the folder with the namespace exists */
	if (git_futils_mkdir_relative(git_buf_cstr(&path), in, 0777,
			GIT_MKDIR_PATH, NULL) < 0)
		goto done;

	/* Return root of the namespaced gitpath, i.e. without the trailing '/refs' */
	git_buf_rtruncate_at_char(&path, '/');
	out = git_buf_detach(&path);

done:
	git_buf_dispose(&path);
	return out;
}