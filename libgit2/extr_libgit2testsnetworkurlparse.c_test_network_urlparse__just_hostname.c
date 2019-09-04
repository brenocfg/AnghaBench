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
 int /*<<< orphan*/  GIT_EINVALIDSPEC ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gitno_extract_url_parts (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  host ; 
 int /*<<< orphan*/  pass ; 
 int /*<<< orphan*/  path ; 
 int /*<<< orphan*/  port ; 
 int /*<<< orphan*/  user ; 

void test_network_urlparse__just_hostname(void)
{
	cl_git_fail_with(GIT_EINVALIDSPEC,
			 gitno_extract_url_parts(&host, &port, &path, &user, &pass,
						 "http://example.com", "8080"));
}