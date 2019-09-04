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
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_is_valid_name (char*) ; 

void test_network_remote_isvalidname__wont_hopefully_choke_on_valid_formats(void)
{
	cl_assert_equal_i(true, git_remote_is_valid_name("webmatrix"));
	cl_assert_equal_i(true, git_remote_is_valid_name("yishaigalatzer/rules"));
}