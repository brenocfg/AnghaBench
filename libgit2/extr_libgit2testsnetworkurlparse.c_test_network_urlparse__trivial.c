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
 int /*<<< orphan*/  cl_assert_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gitno_extract_url_parts (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  host ; 
 int /*<<< orphan*/  pass ; 
 int /*<<< orphan*/  path ; 
 int /*<<< orphan*/  port ; 
 int /*<<< orphan*/  user ; 

void test_network_urlparse__trivial(void)
{
	cl_git_pass(gitno_extract_url_parts(&host, &port, &path, &user, &pass,
				"http://example.com/resource", "8080"));
	cl_assert_equal_s(host, "example.com");
	cl_assert_equal_s(port, "8080");
	cl_assert_equal_s(path, "/resource");
	cl_assert_equal_p(user, NULL);
	cl_assert_equal_p(pass, NULL);
}