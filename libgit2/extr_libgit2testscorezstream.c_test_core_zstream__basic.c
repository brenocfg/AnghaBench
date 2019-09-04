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
typedef  int /*<<< orphan*/  out ;
typedef  int /*<<< orphan*/  git_zstream ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ZSTREAM_DEFLATE ; 
 int /*<<< orphan*/  GIT_ZSTREAM_INIT ; 
 int /*<<< orphan*/  assert_zlib_equal (int /*<<< orphan*/ ,scalar_t__,char*,size_t) ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  data ; 
 int git_zstream_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_zstream_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_zstream_get_output (char*,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_zstream_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_zstream_set_input (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

void test_core_zstream__basic(void)
{
	git_zstream z = GIT_ZSTREAM_INIT;
	char out[128];
	size_t outlen = sizeof(out);

	cl_git_pass(git_zstream_init(&z, GIT_ZSTREAM_DEFLATE));
	cl_git_pass(git_zstream_set_input(&z, data, strlen(data) + 1));
	cl_git_pass(git_zstream_get_output(out, &outlen, &z));
	cl_assert(git_zstream_done(&z));
	cl_assert(outlen > 0);
	git_zstream_free(&z);

	assert_zlib_equal(data, strlen(data) + 1, out, outlen);
}