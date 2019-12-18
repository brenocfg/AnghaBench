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
struct timespec32 {int dummy; } ;
struct timespec {int dummy; } ;
struct thread {int dummy; } ;
struct freebsd32_clock_settime_args {int /*<<< orphan*/  clock_id; int /*<<< orphan*/  tp; } ;
typedef  int /*<<< orphan*/  ats32 ;

/* Variables and functions */
 int /*<<< orphan*/  CP (struct timespec32,struct timespec,int /*<<< orphan*/ ) ; 
 int copyin (int /*<<< orphan*/ ,struct timespec32*,int) ; 
 int kern_clock_settime (struct thread*,int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  tv_nsec ; 
 int /*<<< orphan*/  tv_sec ; 

int
freebsd32_clock_settime(struct thread *td,
			struct freebsd32_clock_settime_args *uap)
{
	struct timespec	ats;
	struct timespec32 ats32;
	int error;

	error = copyin(uap->tp, &ats32, sizeof(ats32));
	if (error)
		return (error);
	CP(ats32, ats, tv_sec);
	CP(ats32, ats, tv_nsec);

	return (kern_clock_settime(td, uap->clock_id, &ats));
}