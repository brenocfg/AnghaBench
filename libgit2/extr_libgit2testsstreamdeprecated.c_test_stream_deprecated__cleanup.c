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
 int GIT_STREAM_STANDARD ; 
 int GIT_STREAM_TLS ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_stream_register (int,int /*<<< orphan*/ *) ; 

void test_stream_deprecated__cleanup(void)
{
	cl_git_pass(git_stream_register(GIT_STREAM_TLS | GIT_STREAM_STANDARD, NULL));
}