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
struct proc {int dummy; } ;
struct filedesc_to_leader {int fdl_refcount; struct filedesc_to_leader* fdl_prev; struct filedesc_to_leader* fdl_next; struct proc* fdl_leader; scalar_t__ fdl_wakeup; scalar_t__ fdl_holdcount; } ;
struct filedesc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILEDESC_XLOCK (struct filedesc*) ; 
 int /*<<< orphan*/  FILEDESC_XUNLOCK (struct filedesc*) ; 
 int /*<<< orphan*/  M_FILEDESC_TO_LEADER ; 
 int /*<<< orphan*/  M_WAITOK ; 
 struct filedesc_to_leader* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct filedesc_to_leader *
filedesc_to_leader_alloc(struct filedesc_to_leader *old, struct filedesc *fdp, struct proc *leader)
{
	struct filedesc_to_leader *fdtol;

	fdtol = malloc(sizeof(struct filedesc_to_leader),
	    M_FILEDESC_TO_LEADER, M_WAITOK);
	fdtol->fdl_refcount = 1;
	fdtol->fdl_holdcount = 0;
	fdtol->fdl_wakeup = 0;
	fdtol->fdl_leader = leader;
	if (old != NULL) {
		FILEDESC_XLOCK(fdp);
		fdtol->fdl_next = old->fdl_next;
		fdtol->fdl_prev = old;
		old->fdl_next = fdtol;
		fdtol->fdl_next->fdl_prev = fdtol;
		FILEDESC_XUNLOCK(fdp);
	} else {
		fdtol->fdl_next = fdtol;
		fdtol->fdl_prev = fdtol;
	}
	return (fdtol);
}