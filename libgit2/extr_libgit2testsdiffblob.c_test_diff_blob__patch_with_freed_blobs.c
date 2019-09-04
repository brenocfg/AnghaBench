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
typedef  int /*<<< orphan*/  git_patch ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;
typedef  int /*<<< orphan*/  git_blob ;

/* Variables and functions */
 int /*<<< orphan*/  BLOB_DIFF ; 
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_blob_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_blob_lookup_prefix (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_oid_fromstrn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_patch_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_from_blobs (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_to_buf (TYPE_1__*,int /*<<< orphan*/ *) ; 

void test_diff_blob__patch_with_freed_blobs(void)
{
	git_oid a_oid, b_oid;
	git_blob *a, *b;
	git_patch *p;
	git_buf buf = GIT_BUF_INIT;

	/* tests/resources/attr/root_test1 */
	cl_git_pass(git_oid_fromstrn(&a_oid, "45141a79", 8));
	cl_git_pass(git_blob_lookup_prefix(&a, g_repo, &a_oid, 4));
	/* tests/resources/attr/root_test2 */
	cl_git_pass(git_oid_fromstrn(&b_oid, "4d713dc4", 8));
	cl_git_pass(git_blob_lookup_prefix(&b, g_repo, &b_oid, 4));

	cl_git_pass(git_patch_from_blobs(&p, a, NULL, b, NULL, NULL));

	git_blob_free(a);
	git_blob_free(b);

	cl_git_pass(git_patch_to_buf(&buf, p));
	cl_assert_equal_s(buf.ptr, BLOB_DIFF);

	git_patch_free(p);
	git_buf_dispose(&buf);
}