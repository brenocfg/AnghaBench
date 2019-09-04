#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct compare_data {int /*<<< orphan*/  attrs; int /*<<< orphan*/  safecrlf; int /*<<< orphan*/  autocrlf; int /*<<< orphan*/  systype; int /*<<< orphan*/  dirname; } ;
struct TYPE_14__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ git_index_entry ;
struct TYPE_15__ {char* ptr; } ;
typedef  TYPE_2__ git_buf ;
typedef  int /*<<< orphan*/  git_blob ;
struct TYPE_16__ {scalar_t__ klass; char* message; } ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 scalar_t__ GIT_ERROR_FILTER ; 
 int /*<<< orphan*/  cl_assert (TYPE_1__ const*) ; 
 int /*<<< orphan*/  cl_fail (char*) ; 
 int /*<<< orphan*/  cl_git_pass (scalar_t__) ; 
 int /*<<< orphan*/  clar__fail (char*,int,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_index ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git__free (char*) ; 
 int /*<<< orphan*/  git_blob_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_blob_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* git_blob_rawcontent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 scalar_t__ git_buf_joinpath (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_buf_printf (TYPE_2__*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ git_buf_puts (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  git_buf_rtrim (TYPE_2__*) ; 
 TYPE_5__* git_error_last () ; 
 scalar_t__ git_futils_readbuffer (TYPE_2__*,char*) ; 
 scalar_t__ git_index_add_bypath (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* git_index_get_bypath (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* git_path_basename (char*) ; 
 scalar_t__ git_path_isfile (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int add_and_check_file(void *payload, git_buf *actual_path)
{
	git_buf expected_path = GIT_BUF_INIT;
	git_buf expected_path_fail = GIT_BUF_INIT;
	git_buf expected_contents = GIT_BUF_INIT;
	struct compare_data *cd = payload;
	char *basename;
	const git_index_entry *entry;
	git_blob *blob;
	bool failed = true;

	basename = git_path_basename(actual_path->ptr);

	if (!strcmp(basename, ".git") || !strcmp(basename, ".gitattributes")) {
		failed = false;
		goto done;
	}

	cl_git_pass(git_buf_joinpath(&expected_path, cd->dirname, basename));

	cl_git_pass(git_buf_puts(&expected_path_fail, expected_path.ptr));
	cl_git_pass(git_buf_puts(&expected_path_fail, ".fail"));

	if (git_path_isfile(expected_path.ptr)) {
		cl_git_pass(git_index_add_bypath(g_index, basename));

		cl_assert(entry = git_index_get_bypath(g_index, basename, 0));
		cl_git_pass(git_blob_lookup(&blob, g_repo, &entry->id));

		cl_git_pass(git_futils_readbuffer(&expected_contents, expected_path.ptr));

		if (strcmp(expected_contents.ptr, git_blob_rawcontent(blob)) != 0)
			goto done;

		git_blob_free(blob);
	} else if (git_path_isfile(expected_path_fail.ptr)) {
		cl_git_pass(git_futils_readbuffer(&expected_contents, expected_path_fail.ptr));
		git_buf_rtrim(&expected_contents);

		if (git_index_add_bypath(g_index, basename) == 0 ||
			git_error_last()->klass != GIT_ERROR_FILTER ||
			strcmp(expected_contents.ptr, git_error_last()->message) != 0)
			goto done;
	} else {
		cl_fail("unexpected index failure");
	}

	failed = false;

done:
	if (failed) {
		git_buf details = GIT_BUF_INIT;
		git_buf_printf(&details, "filename=%s, system=%s, autocrlf=%s, safecrlf=%s, attrs={%s}",
			basename, cd->systype, cd->autocrlf, cd->safecrlf, cd->attrs);
		clar__fail(__FILE__, __LINE__,
			"index contents did not match expected", details.ptr, 0);
		git_buf_dispose(&details);
	}

	git__free(basename);
	git_buf_dispose(&expected_contents);
	git_buf_dispose(&expected_path);
	git_buf_dispose(&expected_path_fail);
	return 0;
}