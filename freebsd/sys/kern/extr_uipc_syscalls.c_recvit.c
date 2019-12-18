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
struct thread {int /*<<< orphan*/  td_proc; } ;
struct msghdr {int msg_flags; int /*<<< orphan*/  msg_namelen; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int MSG_COMPAT ; 
 int /*<<< orphan*/  SV_AOUT ; 
 scalar_t__ SV_PROC_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int copyout (int /*<<< orphan*/ *,void*,int) ; 
 int kern_recvit (struct thread*,int,struct msghdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
recvit(struct thread *td, int s, struct msghdr *mp, void *namelenp)
{
	int error;

	error = kern_recvit(td, s, mp, UIO_USERSPACE, NULL);
	if (error != 0)
		return (error);
	if (namelenp != NULL) {
		error = copyout(&mp->msg_namelen, namelenp, sizeof (socklen_t));
#ifdef COMPAT_OLDSOCK
		if ((mp->msg_flags & MSG_COMPAT) != 0 &&
		    SV_PROC_FLAG(td->td_proc, SV_AOUT))
			error = 0;	/* old recvfrom didn't check */
#endif
	}
	return (error);
}