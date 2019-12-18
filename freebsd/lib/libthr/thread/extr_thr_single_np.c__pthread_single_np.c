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
 int /*<<< orphan*/  _pthread_suspend_all_np () ; 

int
_pthread_single_np(void)
{

	/* Enter single-threaded (non-POSIX) scheduling mode: */
	_pthread_suspend_all_np();
	/*
	 * XXX - Do we want to do this?
	 * __is_threaded = 0;
	 */
	return (0);
}