#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int version; int /*<<< orphan*/  wrap; int /*<<< orphan*/  init; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ git_stream_registration ;
typedef  int /*<<< orphan*/  git_stream ;

/* Variables and functions */
 int GIT_STREAM_STANDARD ; 
 int GIT_STREAM_TLS ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,scalar_t__) ; 
 int /*<<< orphan*/  cl_assert_equal_p (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 scalar_t__ ctor_called ; 
 int /*<<< orphan*/  git_socket_stream_new (int /*<<< orphan*/ **,char*,char*) ; 
 int /*<<< orphan*/  git_stream_register (int,TYPE_1__*) ; 
 int /*<<< orphan*/  git_tls_stream_new (int /*<<< orphan*/ **,char*,char*) ; 
 int /*<<< orphan*/  test_stream ; 
 int /*<<< orphan*/  test_stream_init ; 
 int /*<<< orphan*/  test_stream_wrap ; 

void test_stream_registration__both(void)
{
	git_stream *stream;
	git_stream_registration registration = {0};

	registration.version = 1;
	registration.init = test_stream_init;
	registration.wrap = test_stream_wrap;

	cl_git_pass(git_stream_register(GIT_STREAM_STANDARD | GIT_STREAM_TLS, &registration));

	ctor_called = 0;
	cl_git_pass(git_tls_stream_new(&stream, "localhost", "443"));
	cl_assert_equal_i(1, ctor_called);
	cl_assert_equal_p(&test_stream, stream);

	ctor_called = 0;
	cl_git_pass(git_socket_stream_new(&stream, "localhost", "80"));
	cl_assert_equal_i(1, ctor_called);
	cl_assert_equal_p(&test_stream, stream);
}