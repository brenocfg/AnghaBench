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
struct proc {int p_flag; scalar_t__ p_profthreads; int /*<<< orphan*/  p_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PPAUSE ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int P_PROFIL ; 
 int P_STOPPROF ; 
 int /*<<< orphan*/  cpu_stopprofclock () ; 
 int /*<<< orphan*/  msleep (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ profprocs ; 
 int /*<<< orphan*/  time_lock ; 

void
stopprofclock(struct proc *p)
{

	PROC_LOCK_ASSERT(p, MA_OWNED);
	if (p->p_flag & P_PROFIL) {
		if (p->p_profthreads != 0) {
			while (p->p_profthreads != 0) {
				p->p_flag |= P_STOPPROF;
				msleep(&p->p_profthreads, &p->p_mtx, PPAUSE,
				    "stopprof", 0);
			}
		}
		if ((p->p_flag & P_PROFIL) == 0)
			return;
		p->p_flag &= ~P_PROFIL;
		mtx_lock(&time_lock);
		if (--profprocs == 0)
			cpu_stopprofclock();
		mtx_unlock(&time_lock);
	}
}