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
struct thread {int td_errno; int* td_retval; int /*<<< orphan*/  td_pflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TDP_NERRNO ; 

int
kern_posix_error(struct thread *td, int error)
{

	if (error <= 0)
		return (error);
	td->td_errno = error;
	td->td_pflags |= TDP_NERRNO;
	td->td_retval[0] = error;
	return (0);
}