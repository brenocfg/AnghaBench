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
typedef  int /*<<< orphan*/  stats ;
typedef  int /*<<< orphan*/  git_buf_text_stats ;
typedef  int /*<<< orphan*/  git_buf ;
typedef  int /*<<< orphan*/  git_blob ;

/* Variables and functions */
 int CRLF_NUM_TEST_OBJECTS ; 
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_crlf_filtered_stats ; 
 int /*<<< orphan*/ * g_crlf_oids ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_blob__getbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_blob_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_blob_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_text_gather_stats (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void test_object_blob_filter__stats(void)
{
	int i;
	git_blob *blob;
	git_buf buf = GIT_BUF_INIT;
	git_buf_text_stats stats;

	for (i = 0; i < CRLF_NUM_TEST_OBJECTS; i++) {
		cl_git_pass(git_blob_lookup(&blob, g_repo, &g_crlf_oids[i]));
		cl_git_pass(git_blob__getbuf(&buf, blob));
		git_buf_text_gather_stats(&stats, &buf, false);
		cl_assert_equal_i(
			0, memcmp(&g_crlf_filtered_stats[i], &stats, sizeof(stats)));
		git_blob_free(blob);
	}

	git_buf_dispose(&buf);
}