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
struct TYPE_3__ {int /*<<< orphan*/  use_ssl; int /*<<< orphan*/  pass; int /*<<< orphan*/  user; int /*<<< orphan*/  path; int /*<<< orphan*/  port; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_assert_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_1__ conndata ; 
 int /*<<< orphan*/  gitno_connection_data_from_url (TYPE_1__*,char*,char*) ; 

void test_network_urlparse__connection_data_ssl(void)
{
	cl_git_pass(gitno_connection_data_from_url(&conndata,
				"https://example.com/foo/bar/baz", "bar/baz"));
	cl_assert_equal_s(conndata.host, "example.com");
	cl_assert_equal_s(conndata.port, "443");
	cl_assert_equal_s(conndata.path, "/foo/");
	cl_assert_equal_p(conndata.user, NULL);
	cl_assert_equal_p(conndata.pass, NULL);
	cl_assert_equal_i(conndata.use_ssl, true);
}