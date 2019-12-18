#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t size; char* ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  BIG_STRING_PART ; 
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compress_and_decompress_input_various_ways (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_put (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rand () ; 
 int /*<<< orphan*/  srand (int) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

void test_core_zstream__big_data(void)
{
	git_buf in = GIT_BUF_INIT;
	size_t scan, target;

	for (target = 1024; target <= 1024 * 1024 * 4; target *= 8) {

		/* make a big string that's easy to compress */
		git_buf_clear(&in);
		while (in.size < target)
			cl_git_pass(
				git_buf_put(&in, BIG_STRING_PART, strlen(BIG_STRING_PART)));

		compress_and_decompress_input_various_ways(&in);

		/* make a big string that's hard to compress */
		srand(0xabad1dea);
		for (scan = 0; scan < in.size; ++scan)
			in.ptr[scan] = (char)rand();

		compress_and_decompress_input_various_ways(&in);
	}

	git_buf_dispose(&in);
}