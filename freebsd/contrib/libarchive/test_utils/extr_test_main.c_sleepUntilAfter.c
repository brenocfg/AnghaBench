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
typedef  scalar_t__ time_t ;

/* Variables and functions */
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  sleep (int) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

void
sleepUntilAfter(time_t t)
{
	while (t >= time(NULL))
#if defined(_WIN32) && !defined(__CYGWIN__)
		Sleep(500);
#else
		sleep(1);
#endif
}