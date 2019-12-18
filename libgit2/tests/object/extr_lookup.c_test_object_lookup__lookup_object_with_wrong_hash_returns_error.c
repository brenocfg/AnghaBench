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
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_EMISMATCH ; 
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/  GIT_OPT_ENABLE_STRICT_HASH_VERIFICATION ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_futils_cp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_libgit2_opts (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ ) ; 

void test_object_lookup__lookup_object_with_wrong_hash_returns_error(void)
{
	const char *oldloose = "objects/8e/73b769e97678d684b809b163bebdae2911720f",
	      *newloose = "objects/8e/73b769e97678d684b809b163bebdae2911720e",
	      *commit = "8e73b769e97678d684b809b163bebdae2911720e";
	git_buf oldpath = GIT_BUF_INIT, newpath = GIT_BUF_INIT;
	git_object *object;
	git_oid oid;

	cl_git_pass(git_oid_fromstr(&oid, commit));

	/* Copy object to another location with wrong hash */
	cl_git_pass(git_buf_joinpath(&oldpath, git_repository_path(g_repo), oldloose));
	cl_git_pass(git_buf_joinpath(&newpath, git_repository_path(g_repo), newloose));
	cl_git_pass(git_futils_cp(oldpath.ptr, newpath.ptr, 0644));

	/* Verify that lookup fails due to a hashsum mismatch */
	cl_git_fail_with(GIT_EMISMATCH, git_object_lookup(&object, g_repo, &oid, GIT_OBJECT_COMMIT));

	/* Disable verification and try again */
	cl_git_pass(git_libgit2_opts(GIT_OPT_ENABLE_STRICT_HASH_VERIFICATION, 0));
	cl_git_pass(git_object_lookup(&object, g_repo, &oid, GIT_OBJECT_COMMIT));
	cl_git_pass(git_libgit2_opts(GIT_OPT_ENABLE_STRICT_HASH_VERIFICATION, 1));

	git_object_free(object);
	git_buf_dispose(&oldpath);
	git_buf_dispose(&newpath);
}