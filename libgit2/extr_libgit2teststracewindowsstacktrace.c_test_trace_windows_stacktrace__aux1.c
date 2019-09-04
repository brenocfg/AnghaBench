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

void test_trace_windows_stacktrace__aux1(void)
{
#if defined(GIT_MSVC_CRTDBG)
	git_win32__stack__set_aux_cb(aux_cb_alloc__1, aux_cb_lookup__1);
	c();
	c();
	c();
	c();
	git_win32__stack__set_aux_cb(NULL, NULL);
#endif
}