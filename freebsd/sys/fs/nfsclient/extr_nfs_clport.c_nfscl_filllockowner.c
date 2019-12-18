#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct proc {TYPE_2__* p_stats; int /*<<< orphan*/  p_pid; } ;
typedef  int /*<<< orphan*/  id ;
struct TYPE_3__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_4__ {TYPE_1__ p_start; } ;

/* Variables and functions */
 int F_FLOCK ; 
 int F_POSIX ; 
 scalar_t__ NFSV4CL_LOCKNAMELEN ; 
 int /*<<< orphan*/  bcopy (void**,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*) ; 

void
nfscl_filllockowner(void *id, u_int8_t *cp, int flags)
{
	union {
		u_int32_t	lval;
		u_int8_t	cval[4];
	} tl;
	struct proc *p;

	if (id == NULL) {
		/* Return the single open_owner of all 0 bytes. */
		bzero(cp, NFSV4CL_LOCKNAMELEN);
		return;
	}
	if ((flags & F_POSIX) != 0) {
		p = (struct proc *)id;
		tl.lval = p->p_pid;
		*cp++ = tl.cval[0];
		*cp++ = tl.cval[1];
		*cp++ = tl.cval[2];
		*cp++ = tl.cval[3];
		tl.lval = p->p_stats->p_start.tv_sec;
		*cp++ = tl.cval[0];
		*cp++ = tl.cval[1];
		*cp++ = tl.cval[2];
		*cp++ = tl.cval[3];
		tl.lval = p->p_stats->p_start.tv_usec;
		*cp++ = tl.cval[0];
		*cp++ = tl.cval[1];
		*cp++ = tl.cval[2];
		*cp = tl.cval[3];
	} else if ((flags & F_FLOCK) != 0) {
		bcopy(&id, cp, sizeof(id));
		bzero(&cp[sizeof(id)], NFSV4CL_LOCKNAMELEN - sizeof(id));
	} else {
		printf("nfscl_filllockowner: not F_POSIX or F_FLOCK\n");
		bzero(cp, NFSV4CL_LOCKNAMELEN);
	}
}