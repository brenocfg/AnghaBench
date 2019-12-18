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
typedef  int /*<<< orphan*/  git_trace_level_t ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int written ; 

__attribute__((used)) static void trace_callback(git_trace_level_t level, const char *message)
{
	GIT_UNUSED(level);

	cl_assert(strcmp(message, "Hello world!") == 0);

	written = 1;
}