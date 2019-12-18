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

/* Variables and functions */
 int CRLF_NUM_TEST_OBJECTS ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/ * g_crlf_oids ; 
 int /*<<< orphan*/ * g_crlf_raw ; 
 scalar_t__* g_crlf_raw_len ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_blob_create_from_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

void test_object_blob_filter__initialize(void)
{
	int i;

	g_repo = cl_git_sandbox_init("empty_standard_repo");

	for (i = 0; i < CRLF_NUM_TEST_OBJECTS; i++) {
		if (g_crlf_raw_len[i] < 0)
			g_crlf_raw_len[i] = strlen(g_crlf_raw[i]);

		cl_git_pass(git_blob_create_from_buffer(
			&g_crlf_oids[i], g_repo, g_crlf_raw[i], (size_t)g_crlf_raw_len[i]));
	}
}