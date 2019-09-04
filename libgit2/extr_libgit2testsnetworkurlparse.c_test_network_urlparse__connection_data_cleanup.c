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
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conndata ; 
 int /*<<< orphan*/  gitno_connection_data_from_url (int /*<<< orphan*/ *,char*,char*) ; 

void test_network_urlparse__connection_data_cleanup(void)
{
	cl_git_pass(gitno_connection_data_from_url(&conndata,
				"http://foo.com/bar/baz/biff", "baz/biff"));
	cl_git_pass(gitno_connection_data_from_url(&conndata,
				"https://foo.com/bar/baz/biff", "baz/biff"));
}