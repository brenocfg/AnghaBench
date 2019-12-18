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
typedef  enum exit_status_type { ____Placeholder_exit_status_type } exit_status_type ;

/* Variables and functions */
 int E_ERROR ; 
 int E_WARNING ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int exit_status ; 
 int /*<<< orphan*/  exit_status_cs ; 

extern void
set_exit_status(enum exit_status_type new_status)
{
	assert(new_status == E_WARNING || new_status == E_ERROR);

#if defined(_WIN32) && !defined(__CYGWIN__)
	EnterCriticalSection(&exit_status_cs);
#endif

	if (exit_status != E_ERROR)
		exit_status = new_status;

#if defined(_WIN32) && !defined(__CYGWIN__)
	LeaveCriticalSection(&exit_status_cs);
#endif

	return;
}