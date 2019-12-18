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
struct futimesat_args {int /*<<< orphan*/  times; int /*<<< orphan*/  path; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int kern_utimesat (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sys_futimesat(struct thread *td, struct futimesat_args *uap)
{

	return (kern_utimesat(td, uap->fd, uap->path, UIO_USERSPACE,
	    uap->times, UIO_USERSPACE));
}