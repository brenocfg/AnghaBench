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
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conndata ; 
 int /*<<< orphan*/  git_net_url_parse (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gitno_connection_data_handle_redirect (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

void test_network_redirect__redirect_cross_host_denied(void)
{
	cl_git_pass(git_net_url_parse(&conndata, "https://bar.com/bar/baz"));
	cl_git_fail_with(gitno_connection_data_handle_redirect(&conndata,
				"https://foo.com/bar/baz", NULL),
			-1);
}