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
union sigval {int /*<<< orphan*/  sival_int; } ;
typedef  int /*<<< orphan*/  sv ;
struct thread {int dummy; } ;
struct freebsd32_sigqueue_args {int /*<<< orphan*/  signum; int /*<<< orphan*/  pid; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (union sigval*,int) ; 
 int kern_sigqueue (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union sigval*) ; 

int
freebsd32_sigqueue(struct thread *td, struct freebsd32_sigqueue_args *uap)
{
	union sigval sv;

	/*
	 * On 32-bit ABIs, sival_int and sival_ptr are the same.
	 * On 64-bit little-endian ABIs, the low bits are the same.
	 * In 64-bit big-endian ABIs, sival_int overlaps with
	 * sival_ptr's HIGH bits.  We choose to support sival_int
	 * rather than sival_ptr in this case as it seems to be
	 * more common.
	 */
	bzero(&sv, sizeof(sv));
	sv.sival_int = uap->value;

	return (kern_sigqueue(td, uap->pid, uap->signum, &sv));
}