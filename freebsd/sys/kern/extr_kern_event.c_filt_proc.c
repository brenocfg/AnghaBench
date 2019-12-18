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
typedef  int u_int ;
struct proc {int /*<<< orphan*/  p_xsig; int /*<<< orphan*/  p_xexit; } ;
struct TYPE_2__ {struct proc* p_proc; } ;
struct knote {int kn_sfflags; int kn_fflags; int kn_flags; int /*<<< orphan*/  kn_data; TYPE_1__ kn_ptr; } ;

/* Variables and functions */
 int EV_DROP ; 
 int EV_EOF ; 
 int EV_ONESHOT ; 
 int /*<<< orphan*/  KW_EXITCODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NOTE_EXIT ; 
 int NOTE_PCTRLMASK ; 

__attribute__((used)) static int
filt_proc(struct knote *kn, long hint)
{
	struct proc *p;
	u_int event;

	p = kn->kn_ptr.p_proc;
	if (p == NULL) /* already activated, from attach filter */
		return (0);

	/* Mask off extra data. */
	event = (u_int)hint & NOTE_PCTRLMASK;

	/* If the user is interested in this event, record it. */
	if (kn->kn_sfflags & event)
		kn->kn_fflags |= event;

	/* Process is gone, so flag the event as finished. */
	if (event == NOTE_EXIT) {
		kn->kn_flags |= EV_EOF | EV_ONESHOT;
		kn->kn_ptr.p_proc = NULL;
		if (kn->kn_fflags & NOTE_EXIT)
			kn->kn_data = KW_EXITCODE(p->p_xexit, p->p_xsig);
		if (kn->kn_fflags == 0)
			kn->kn_flags |= EV_DROP;
		return (1);
	}

	return (kn->kn_fflags != 0);
}