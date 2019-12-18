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
struct freebsd32_clock_nanosleep_args {int /*<<< orphan*/  rmtp; int /*<<< orphan*/  rqtp; int /*<<< orphan*/  flags; int /*<<< orphan*/  clock_id; } ;

/* Variables and functions */
 int freebsd32_user_clock_nanosleep (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kern_posix_error (struct thread*,int) ; 

int
freebsd32_clock_nanosleep(struct thread *td,
    struct freebsd32_clock_nanosleep_args *uap)
{
	int error;

	error = freebsd32_user_clock_nanosleep(td, uap->clock_id, uap->flags,
	    uap->rqtp, uap->rmtp);
	return (kern_posix_error(td, error));
}