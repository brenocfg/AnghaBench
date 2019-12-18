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
 int /*<<< orphan*/  git__allocator ; 
 int git_stdalloc_init_allocator (int /*<<< orphan*/ *) ; 
 int git_win32_crtdbg_init_allocator (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int setup_default_allocator(void)
{
#if defined(GIT_MSVC_CRTDBG)
	return git_win32_crtdbg_init_allocator(&git__allocator);
#else
	return git_stdalloc_init_allocator(&git__allocator);
#endif
}