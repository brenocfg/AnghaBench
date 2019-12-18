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
struct timeval {int dummy; } ;
struct timespec32 {int dummy; } ;
struct timespec {int dummy; } ;
struct thread {int dummy; } ;
struct freebsd32_pselect_args {int /*<<< orphan*/  ex; int /*<<< orphan*/  ou; int /*<<< orphan*/  in; int /*<<< orphan*/  nd; int /*<<< orphan*/ * sm; int /*<<< orphan*/ * ts; } ;
typedef  struct timespec32 sigset_t ;
typedef  int /*<<< orphan*/  set ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CP (struct timespec32,struct timespec,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMESPEC_TO_TIMEVAL (struct timeval*,struct timespec*) ; 
 int copyin (int /*<<< orphan*/ *,struct timespec32*,int) ; 
 int kern_pselect (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval*,struct timespec32*,int) ; 
 int /*<<< orphan*/  tv_nsec ; 
 int /*<<< orphan*/  tv_sec ; 

int
freebsd32_pselect(struct thread *td, struct freebsd32_pselect_args *uap)
{
	struct timespec32 ts32;
	struct timespec ts;
	struct timeval tv, *tvp;
	sigset_t set, *uset;
	int error;

	if (uap->ts != NULL) {
		error = copyin(uap->ts, &ts32, sizeof(ts32));
		if (error != 0)
			return (error);
		CP(ts32, ts, tv_sec);
		CP(ts32, ts, tv_nsec);
		TIMESPEC_TO_TIMEVAL(&tv, &ts);
		tvp = &tv;
	} else
		tvp = NULL;
	if (uap->sm != NULL) {
		error = copyin(uap->sm, &set, sizeof(set));
		if (error != 0)
			return (error);
		uset = &set;
	} else
		uset = NULL;
	/*
	 * XXX Do pointers need PTRIN()?
	 */
	error = kern_pselect(td, uap->nd, uap->in, uap->ou, uap->ex, tvp,
	    uset, sizeof(int32_t) * 8);
	return (error);
}