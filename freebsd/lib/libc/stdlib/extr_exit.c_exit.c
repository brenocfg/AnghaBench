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
 int /*<<< orphan*/  __cleanup () ; 
 int /*<<< orphan*/  __cxa_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __cxa_thread_call_dtors () ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  stub1 () ; 

void
exit(int status)
{
	/* Ensure that the auto-initialization routine is linked in: */
	extern int _thread_autoinit_dummy_decl;

	_thread_autoinit_dummy_decl = 1;

	/*
	 * We're dealing with cleaning up thread_local destructors in the case of
	 * the process termination through main() exit.
	 * Other cases are handled elsewhere.
	 */
	__cxa_thread_call_dtors();
	__cxa_finalize(NULL);
	if (__cleanup)
		(*__cleanup)();
	_exit(status);
}