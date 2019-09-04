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
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 scalar_t__ CreateEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ _beginthreadex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int errno ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  ticktack ; 
 scalar_t__ timer_event ; 
 scalar_t__ timer_thread ; 

__attribute__((used)) static int start_timer_thread(void)
{
	timer_event = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (timer_event) {
		timer_thread = (HANDLE) _beginthreadex(NULL, 0, ticktack, NULL, 0, NULL);
		if (!timer_thread )
			return errno = ENOMEM,
				error("cannot start timer thread");
	} else
		return errno = ENOMEM,
			error("cannot allocate resources for timer");
	return 0;
}