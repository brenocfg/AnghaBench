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
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  cl_repo_set_bool (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  count_fsyncs (size_t*,size_t*) ; 
 int /*<<< orphan*/  expected_fsyncs_compress ; 
 int /*<<< orphan*/  expected_fsyncs_create ; 
 int /*<<< orphan*/  g_repo ; 

void test_refs_create__fsyncs_when_repo_config_set(void)
{
	size_t create_count, compress_count;

	cl_repo_set_bool(g_repo, "core.fsyncObjectFiles", true);

	count_fsyncs(&create_count, &compress_count);

	cl_assert_equal_i(expected_fsyncs_create, create_count);
	cl_assert_equal_i(expected_fsyncs_compress, compress_count);
}