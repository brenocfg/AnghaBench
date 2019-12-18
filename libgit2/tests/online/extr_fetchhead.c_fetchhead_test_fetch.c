#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int count; char** strings; } ;
typedef  TYPE_1__ git_strarray ;
typedef  int /*<<< orphan*/  git_remote ;
struct TYPE_11__ {int /*<<< orphan*/  download_tags; } ;
typedef  TYPE_2__ git_fetch_options ;
struct TYPE_12__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_3__ git_buf ;

/* Variables and functions */
 TYPE_3__ GIT_BUF_INIT ; 
 TYPE_2__ GIT_FETCH_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_REMOTE_DOWNLOAD_TAGS_AUTO ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_3__*) ; 
 int /*<<< orphan*/  git_futils_readbuffer (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  git_remote_fetch (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void fetchhead_test_fetch(const char *fetchspec, const char *expected_fetchhead)
{
	git_remote *remote;
	git_fetch_options fetch_opts = GIT_FETCH_OPTIONS_INIT;
	git_buf fetchhead_buf = GIT_BUF_INIT;
	int equals = 0;
	git_strarray array, *active_refs = NULL;

	cl_git_pass(git_remote_lookup(&remote, g_repo, "origin"));
	fetch_opts.download_tags = GIT_REMOTE_DOWNLOAD_TAGS_AUTO;

	if(fetchspec != NULL) {
		array.count = 1;
		array.strings = (char **) &fetchspec;
		active_refs = &array;
	}

	cl_git_pass(git_remote_fetch(remote, active_refs, &fetch_opts, NULL));
	git_remote_free(remote);

	cl_git_pass(git_futils_readbuffer(&fetchhead_buf, "./foo/.git/FETCH_HEAD"));

	equals = (strcmp(fetchhead_buf.ptr, expected_fetchhead) == 0);

	git_buf_dispose(&fetchhead_buf);

	cl_assert(equals);
}