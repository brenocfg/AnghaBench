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
 size_t ARRAY_SIZE (size_t*) ; 
 int /*<<< orphan*/  commit ; 
 int /*<<< orphan*/  one ; 
 int /*<<< orphan*/  some ; 
 int /*<<< orphan*/  tag ; 
 int /*<<< orphan*/  test_readstream_object (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  tree ; 
 int /*<<< orphan*/  two ; 
 int /*<<< orphan*/  zero ; 

void test_odb_loose__streaming_reads(void)
{
	size_t blocksizes[] = { 1, 2, 4, 16, 99, 1024, 123456789 };
	size_t i;

	for (i = 0; i < ARRAY_SIZE(blocksizes); i++) {
		test_readstream_object(&commit, blocksizes[i]);
		test_readstream_object(&tree, blocksizes[i]);
		test_readstream_object(&tag, blocksizes[i]);
		test_readstream_object(&zero, blocksizes[i]);
		test_readstream_object(&one, blocksizes[i]);
		test_readstream_object(&two, blocksizes[i]);
		test_readstream_object(&some, blocksizes[i]);
	}
}