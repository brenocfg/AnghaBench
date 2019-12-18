#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  password; int /*<<< orphan*/  username; int /*<<< orphan*/  path; int /*<<< orphan*/  port; int /*<<< orphan*/  host; int /*<<< orphan*/  scheme; } ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_1__ conndata ; 
 int /*<<< orphan*/  git_net_url_parse (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  gitno_connection_data_handle_redirect (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 

void test_network_redirect__redirect_relative(void)
{
	cl_git_pass(git_net_url_parse(&conndata, "http://foo.com/bar/baz/biff"));
	cl_git_pass(gitno_connection_data_handle_redirect(&conndata,
				"/zap/baz/biff?bam", NULL));
	cl_assert_equal_s(conndata.scheme, "http");
	cl_assert_equal_s(conndata.host, "foo.com");
	cl_assert_equal_s(conndata.port, "80");
	cl_assert_equal_s(conndata.path, "/zap/baz/biff?bam");
	cl_assert_equal_p(conndata.username, NULL);
	cl_assert_equal_p(conndata.password, NULL);
}