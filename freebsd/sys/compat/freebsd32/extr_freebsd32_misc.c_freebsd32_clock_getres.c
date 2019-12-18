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
typedef  int /*<<< orphan*/  ts32 ;
struct timespec32 {int dummy; } ;
struct timespec {int dummy; } ;
struct thread {int dummy; } ;
struct freebsd32_clock_getres_args {int /*<<< orphan*/ * tp; int /*<<< orphan*/  clock_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP (struct timespec,struct timespec32,int /*<<< orphan*/ ) ; 
 int copyout (struct timespec32*,int /*<<< orphan*/ *,int) ; 
 int kern_clock_getres (struct thread*,int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  tv_nsec ; 
 int /*<<< orphan*/  tv_sec ; 

int
freebsd32_clock_getres(struct thread *td,
		       struct freebsd32_clock_getres_args *uap)
{
	struct timespec	ts;
	struct timespec32 ts32;
	int error;

	if (uap->tp == NULL)
		return (0);
	error = kern_clock_getres(td, uap->clock_id, &ts);
	if (error == 0) {
		CP(ts, ts32, tv_sec);
		CP(ts, ts32, tv_nsec);
		error = copyout(&ts32, uap->tp, sizeof(ts32));
	}
	return (error);
}