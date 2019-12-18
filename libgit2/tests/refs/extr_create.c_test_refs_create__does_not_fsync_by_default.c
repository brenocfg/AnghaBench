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
 int /*<<< orphan*/  count_fsyncs (size_t*,size_t*) ; 

void test_refs_create__does_not_fsync_by_default(void)
{
	size_t create_count, compress_count;
	count_fsyncs(&create_count, &compress_count);

	cl_assert_equal_i(0, create_count);
	cl_assert_equal_i(0, compress_count);
}