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
struct TYPE_3__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int) ; 
 TYPE_1__ conndata ; 
 int /*<<< orphan*/  git__strdup (char*) ; 
 int /*<<< orphan*/  gitno_connection_data_from_url (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 

void test_network_urlparse__connection_data_cross_host_redirect(void)
{
	conndata.host = git__strdup("bar.com");
	cl_git_fail_with(gitno_connection_data_from_url(&conndata,
				"https://foo.com/bar/baz", NULL),
			-1);
}