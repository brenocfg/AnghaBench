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
struct TYPE_3__ {int flags; int /*<<< orphan*/  to; int /*<<< orphan*/  from; } ;
typedef  TYPE_1__ git_revspec ;
typedef  scalar_t__ git_revparse_mode_t ;
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 scalar_t__ GIT_ENOTFOUND ; 
 int /*<<< orphan*/  cl_assert_equal_i (scalar_t__,int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,char const*) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_object_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fmt (char*,int /*<<< orphan*/ ) ; 
 int git_revparse (TYPE_1__*,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void test_id_inrepo(
	const char *spec,
	const char *expected_left,
	const char *expected_right,
	git_revparse_mode_t expected_flags,
	git_repository *repo)
{
	git_revspec revspec;
	int error = git_revparse(&revspec, repo, spec);

	if (expected_left) {
		char str[64] = {0};
		cl_assert_equal_i(0, error);
		git_oid_fmt(str, git_object_id(revspec.from));
		cl_assert_equal_s(str, expected_left);
		git_object_free(revspec.from);
	} else {
		cl_assert_equal_i(GIT_ENOTFOUND, error);
	}

	if (expected_right) {
		char str[64] = {0};
		git_oid_fmt(str, git_object_id(revspec.to));
		cl_assert_equal_s(str, expected_right);
		git_object_free(revspec.to);
	}

	if (expected_flags)
		cl_assert_equal_i(expected_flags, revspec.flags);
}