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
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_1__ conndata ; 
 int /*<<< orphan*/  git_net_url_is_default_port (TYPE_1__*) ; 
 int /*<<< orphan*/  git_net_url_parse (TYPE_1__*,char*) ; 

void test_network_urlparse__encoded_password(void)
{
	cl_git_pass(git_net_url_parse(&conndata,
				"https://user:pass%2fis%40bad@hostname.com:1234/"));
	cl_assert_equal_s(conndata.scheme, "https");
	cl_assert_equal_s(conndata.host, "hostname.com");
	cl_assert_equal_s(conndata.port, "1234");
	cl_assert_equal_s(conndata.path, "/");
	cl_assert_equal_s(conndata.username, "user");
	cl_assert_equal_s(conndata.password, "pass/is@bad");
	cl_assert_equal_i(git_net_url_is_default_port(&conndata), 0);
}