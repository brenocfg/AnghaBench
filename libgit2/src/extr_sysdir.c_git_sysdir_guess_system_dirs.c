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
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int git_buf_sets (int /*<<< orphan*/ *,char*) ; 
 int git_win32__find_system_dirs (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int git_sysdir_guess_system_dirs(git_buf *out)
{
#ifdef GIT_WIN32
	return git_win32__find_system_dirs(out, L"etc\\");
#else
	return git_buf_sets(out, "/etc");
#endif
}