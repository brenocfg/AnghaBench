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
typedef  scalar_t__ u_int8_t ;
typedef  scalar_t__ u_int32_t ;
struct proc {TYPE_2__* p_stats; } ;
typedef  scalar_t__ pid_t ;
struct TYPE_3__ {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_4__ {TYPE_1__ p_start; } ;

/* Variables and functions */
 int NFSV4CL_LOCKNAMELEN ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 struct proc* pfind_any_locked (scalar_t__) ; 

int
nfscl_procdoesntexist(u_int8_t *own)
{
	union {
		u_int32_t	lval;
		u_int8_t	cval[4];
	} tl;
	struct proc *p;
	pid_t pid;
	int i, ret = 0;

	/* For the single open_owner of all 0 bytes, just return 0. */
	for (i = 0; i < NFSV4CL_LOCKNAMELEN; i++)
		if (own[i] != 0)
			break;
	if (i == NFSV4CL_LOCKNAMELEN)
		return (0);

	tl.cval[0] = *own++;
	tl.cval[1] = *own++;
	tl.cval[2] = *own++;
	tl.cval[3] = *own++;
	pid = tl.lval;
	p = pfind_any_locked(pid);
	if (p == NULL)
		return (1);
	if (p->p_stats == NULL) {
		PROC_UNLOCK(p);
		return (0);
	}
	tl.cval[0] = *own++;
	tl.cval[1] = *own++;
	tl.cval[2] = *own++;
	tl.cval[3] = *own++;
	if (tl.lval != p->p_stats->p_start.tv_sec) {
		ret = 1;
	} else {
		tl.cval[0] = *own++;
		tl.cval[1] = *own++;
		tl.cval[2] = *own++;
		tl.cval[3] = *own;
		if (tl.lval != p->p_stats->p_start.tv_usec)
			ret = 1;
	}
	PROC_UNLOCK(p);
	return (ret);
}