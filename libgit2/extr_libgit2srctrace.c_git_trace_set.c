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
typedef  int /*<<< orphan*/  git_trace_callback ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  GIT_UNUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 

int git_trace_set(git_trace_level_t level, git_trace_callback callback)
{
#ifdef GIT_TRACE
	assert(level == 0 || callback != NULL);

	git_trace__data.level = level;
	git_trace__data.callback = callback;
	GIT_MEMORY_BARRIER;

	return 0;
#else
	GIT_UNUSED(level);
	GIT_UNUSED(callback);

	git_error_set(GIT_ERROR_INVALID,
		"this version of libgit2 was not built with tracing.");
	return -1;
#endif
}