#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_patch ;
struct TYPE_6__ {int /*<<< orphan*/  id; int /*<<< orphan*/  size; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; int /*<<< orphan*/  size; } ;
struct TYPE_7__ {int status; TYPE_2__ new_file; TYPE_1__ old_file; } ;
typedef  TYPE_3__ git_diff_delta ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DELTA_UNMODIFIED ; 
 int /*<<< orphan*/ * alien ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_assert_equal_sz (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * d ; 
 int /*<<< orphan*/  git_blob_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_blob_rawsize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_from_blobs (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* git_patch_get_delta (int /*<<< orphan*/ *) ; 
 scalar_t__ git_patch_num_hunks (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opts ; 

void test_diff_blob__can_compare_identical_blobs_with_patch(void)
{
	git_patch *p;
	const git_diff_delta *delta;

	cl_git_pass(git_patch_from_blobs(&p, d, NULL, d, NULL, &opts));
	cl_assert(p != NULL);

	delta = git_patch_get_delta(p);
	cl_assert(delta != NULL);
	cl_assert_equal_i(GIT_DELTA_UNMODIFIED, delta->status);
	cl_assert_equal_sz(delta->old_file.size, git_blob_rawsize(d));
	cl_assert_equal_oid(git_blob_id(d), &delta->old_file.id);
	cl_assert_equal_sz(delta->new_file.size, git_blob_rawsize(d));
	cl_assert_equal_oid(git_blob_id(d), &delta->new_file.id);

	cl_assert_equal_i(0, (int)git_patch_num_hunks(p));
	git_patch_free(p);

	cl_git_pass(git_patch_from_blobs(&p, NULL, NULL, NULL, NULL, &opts));
	cl_assert(p != NULL);

	delta = git_patch_get_delta(p);
	cl_assert(delta != NULL);
	cl_assert_equal_i(GIT_DELTA_UNMODIFIED, delta->status);
	cl_assert_equal_sz(0, delta->old_file.size);
	cl_assert(git_oid_is_zero(&delta->old_file.id));
	cl_assert_equal_sz(0, delta->new_file.size);
	cl_assert(git_oid_is_zero(&delta->new_file.id));

	cl_assert_equal_i(0, (int)git_patch_num_hunks(p));
	git_patch_free(p);

	cl_git_pass(git_patch_from_blobs(&p, alien, NULL, alien, NULL, &opts));
	cl_assert(p != NULL);
	cl_assert_equal_i(GIT_DELTA_UNMODIFIED, git_patch_get_delta(p)->status);
	cl_assert_equal_i(0, (int)git_patch_num_hunks(p));
	git_patch_free(p);
}