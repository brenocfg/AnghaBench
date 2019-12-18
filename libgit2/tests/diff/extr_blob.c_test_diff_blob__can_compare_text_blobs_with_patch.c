#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  git_patch ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_blob ;

/* Variables and functions */
 int /*<<< orphan*/  assert_patch_matches_blobs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * d ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_blob_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_blob_lookup_prefix (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_oid_fromstrn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_patch_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_from_blobs (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opts ; 

void test_diff_blob__can_compare_text_blobs_with_patch(void)
{
	git_blob *a, *b, *c;
	git_oid a_oid, b_oid, c_oid;
	git_patch *p;

	/* tests/resources/attr/root_test1 */
	cl_git_pass(git_oid_fromstrn(&a_oid, "45141a79", 8));
	cl_git_pass(git_blob_lookup_prefix(&a, g_repo, &a_oid, 8));

	/* tests/resources/attr/root_test2 */
	cl_git_pass(git_oid_fromstrn(&b_oid, "4d713dc4", 8));
	cl_git_pass(git_blob_lookup_prefix(&b, g_repo, &b_oid, 8));

	/* tests/resources/attr/root_test3 */
	cl_git_pass(git_oid_fromstrn(&c_oid, "c96bbb2c2557a832", 16));
	cl_git_pass(git_blob_lookup_prefix(&c, g_repo, &c_oid, 16));

	/* Doing the equivalent of a `git diff -U1` on these files */

	/* diff on tests/resources/attr/root_test1 */
	cl_git_pass(git_patch_from_blobs(&p, a, NULL, b, NULL, &opts));
	assert_patch_matches_blobs(p, a, b, 1, 6, 0, 1, 5, 0);
	git_patch_free(p);

	/* diff on tests/resources/attr/root_test2 */
	cl_git_pass(git_patch_from_blobs(&p, b, NULL, c, NULL, &opts));
	assert_patch_matches_blobs(p, b, c, 1, 15, 0, 3, 9, 3);
	git_patch_free(p);

	/* diff on tests/resources/attr/root_test3 */
	cl_git_pass(git_patch_from_blobs(&p, a, NULL, c, NULL, &opts));
	assert_patch_matches_blobs(p, a, c, 1, 13, 0, 0, 12, 1);
	git_patch_free(p);

	/* one more */
	cl_git_pass(git_patch_from_blobs(&p, c, NULL, d, NULL, &opts));
	assert_patch_matches_blobs(p, c, d, 2, 5, 9, 4, 6, 4);
	git_patch_free(p);

	git_blob_free(a);
	git_blob_free(b);
	git_blob_free(c);
}