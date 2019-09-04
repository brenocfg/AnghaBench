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
typedef  int /*<<< orphan*/  git_blob ;

/* Variables and functions */
 int CRLF_NUM_TEST_OBJECTS ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_sz (size_t,size_t) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_crlf_oids ; 
 int /*<<< orphan*/ * g_crlf_raw ; 
 scalar_t__* g_crlf_raw_len ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_blob_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_blob_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_blob_rawcontent (int /*<<< orphan*/ *) ; 
 scalar_t__ git_blob_rawsize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

void test_object_blob_filter__unfiltered(void)
{
	int i;
	git_blob *blob;

	for (i = 0; i < CRLF_NUM_TEST_OBJECTS; i++) {
		size_t raw_len = (size_t)g_crlf_raw_len[i];

		cl_git_pass(git_blob_lookup(&blob, g_repo, &g_crlf_oids[i]));

		cl_assert_equal_sz(raw_len, (size_t)git_blob_rawsize(blob));
		cl_assert_equal_i(
			0, memcmp(g_crlf_raw[i], git_blob_rawcontent(blob), raw_len));

		git_blob_free(blob);
	}
}