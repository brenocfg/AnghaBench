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
struct TYPE_3__ {int /*<<< orphan*/  to; int /*<<< orphan*/  from; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_revspec ;
typedef  int git_revparse_mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,char const*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_object_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fmt (char*,int /*<<< orphan*/ ) ; 
 int git_revparse (TYPE_1__*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void test_rangelike(const char *rangelike,
						   const char *expected_left,
						   const char *expected_right,
						   git_revparse_mode_t expected_revparseflags)
{
	char objstr[64] = {0};
	git_revspec revspec;
	int error;

	error = git_revparse(&revspec, g_repo, rangelike);

	if (expected_left != NULL) {
		cl_assert_equal_i(0, error);
		cl_assert_equal_i(revspec.flags, expected_revparseflags);
		git_oid_fmt(objstr, git_object_id(revspec.from));
		cl_assert_equal_s(objstr, expected_left);
		git_oid_fmt(objstr, git_object_id(revspec.to));
		cl_assert_equal_s(objstr, expected_right);
	} else
		cl_assert(error != 0);

	git_object_free(revspec.from);
	git_object_free(revspec.to);
}