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
typedef  int /*<<< orphan*/  git_stream ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,scalar_t__) ; 
 int /*<<< orphan*/  cl_assert_equal_p (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_fail_with (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int) ; 
 scalar_t__ ctor_called ; 
 int /*<<< orphan*/  git_stream_free (int /*<<< orphan*/ *) ; 
 int git_stream_register_tls (int /*<<< orphan*/ *) ; 
 int git_tls_stream_new (int /*<<< orphan*/ **,char*,char*) ; 
 int /*<<< orphan*/  test_stream ; 
 int /*<<< orphan*/ * test_stream_init ; 

void test_stream_deprecated__register_tls(void)
{
	git_stream *stream;
	int error;

	ctor_called = 0;
	cl_git_pass(git_stream_register_tls(test_stream_init));
	cl_git_pass(git_tls_stream_new(&stream, "localhost", "443"));
	cl_assert_equal_i(1, ctor_called);
	cl_assert_equal_p(&test_stream, stream);

	ctor_called = 0;
	stream = NULL;
	cl_git_pass(git_stream_register_tls(NULL));
	error = git_tls_stream_new(&stream, "localhost", "443");

	/*
	 * We don't have TLS support enabled, or we're on Windows,
	 * which has no arbitrary TLS stream support.
	 */
#if defined(GIT_WIN32) || !defined(GIT_HTTPS)
	cl_git_fail_with(-1, error);
#else
	cl_git_pass(error);
#endif

	cl_assert_equal_i(0, ctor_called);
	cl_assert(&test_stream != stream);

	git_stream_free(stream);
}