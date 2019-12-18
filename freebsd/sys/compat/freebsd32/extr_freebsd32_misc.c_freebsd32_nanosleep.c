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
struct thread {int dummy; } ;
struct freebsd32_nanosleep_args {int /*<<< orphan*/  rmtp; int /*<<< orphan*/  rqtp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  TIMER_RELTIME ; 
 int freebsd32_user_clock_nanosleep (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
freebsd32_nanosleep(struct thread *td, struct freebsd32_nanosleep_args *uap)
{

	return (freebsd32_user_clock_nanosleep(td, CLOCK_REALTIME,
	    TIMER_RELTIME, uap->rqtp, uap->rmtp));
}