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
struct timespec {int dummy; } ;
typedef  int /*<<< orphan*/  sem_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  TIMER_ABSTIME ; 
 int _sem_clockwait_np (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timespec const*,int /*<<< orphan*/ *) ; 

int
_sem_timedwait(sem_t * __restrict sem,
	const struct timespec * __restrict abstime)
{

	return (_sem_clockwait_np(sem, CLOCK_REALTIME, TIMER_ABSTIME, abstime,
	    NULL));
}