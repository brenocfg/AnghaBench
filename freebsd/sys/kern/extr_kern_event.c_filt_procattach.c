#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct proc {int p_flag; int /*<<< orphan*/  p_klist; } ;
struct TYPE_2__ {struct proc* p_proc; } ;
struct knote {int kn_sfflags; int kn_flags; int /*<<< orphan*/  kn_fflags; int /*<<< orphan*/  kn_sdata; int /*<<< orphan*/  kn_data; TYPE_1__ kn_ptr; int /*<<< orphan*/  kn_id; } ;

/* Variables and functions */
 int ESRCH ; 
 int EV_CLEAR ; 
 int EV_FLAG1 ; 
 int EV_FLAG2 ; 
 int /*<<< orphan*/  KNOTE_ACTIVATE (struct knote*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NOTE_CHILD ; 
 int NOTE_EXEC ; 
 int NOTE_EXIT ; 
 int NOTE_FORK ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int P_WEXIT ; 
 int /*<<< orphan*/  curthread ; 
 scalar_t__ filt_proc (struct knote*,int) ; 
 int /*<<< orphan*/  knlist_add (int /*<<< orphan*/ ,struct knote*,int) ; 
 int p_cansee (int /*<<< orphan*/ ,struct proc*) ; 
 struct proc* pfind (int /*<<< orphan*/ ) ; 
 struct proc* pfind_any (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
filt_procattach(struct knote *kn)
{
	struct proc *p;
	int error;
	bool exiting, immediate;

	exiting = immediate = false;
	if (kn->kn_sfflags & NOTE_EXIT)
		p = pfind_any(kn->kn_id);
	else
		p = pfind(kn->kn_id);
	if (p == NULL)
		return (ESRCH);
	if (p->p_flag & P_WEXIT)
		exiting = true;

	if ((error = p_cansee(curthread, p))) {
		PROC_UNLOCK(p);
		return (error);
	}

	kn->kn_ptr.p_proc = p;
	kn->kn_flags |= EV_CLEAR;		/* automatically set */

	/*
	 * Internal flag indicating registration done by kernel for the
	 * purposes of getting a NOTE_CHILD notification.
	 */
	if (kn->kn_flags & EV_FLAG2) {
		kn->kn_flags &= ~EV_FLAG2;
		kn->kn_data = kn->kn_sdata;		/* ppid */
		kn->kn_fflags = NOTE_CHILD;
		kn->kn_sfflags &= ~(NOTE_EXIT | NOTE_EXEC | NOTE_FORK);
		immediate = true; /* Force immediate activation of child note. */
	}
	/*
	 * Internal flag indicating registration done by kernel (for other than
	 * NOTE_CHILD).
	 */
	if (kn->kn_flags & EV_FLAG1) {
		kn->kn_flags &= ~EV_FLAG1;
	}

	knlist_add(p->p_klist, kn, 1);

	/*
	 * Immediately activate any child notes or, in the case of a zombie
	 * target process, exit notes.  The latter is necessary to handle the
	 * case where the target process, e.g. a child, dies before the kevent
	 * is registered.
	 */
	if (immediate || (exiting && filt_proc(kn, NOTE_EXIT)))
		KNOTE_ACTIVATE(kn, 0);

	PROC_UNLOCK(p);

	return (0);
}