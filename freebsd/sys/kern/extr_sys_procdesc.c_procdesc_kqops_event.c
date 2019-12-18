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
struct procdesc {int pd_flags; int /*<<< orphan*/  pd_xstat; } ;
struct knote {int kn_sfflags; int kn_fflags; int kn_flags; int /*<<< orphan*/  kn_data; TYPE_1__* kn_fp; } ;
struct TYPE_2__ {struct procdesc* f_data; } ;

/* Variables and functions */
 int EV_DROP ; 
 int EV_EOF ; 
 int EV_ONESHOT ; 
 int NOTE_EXIT ; 
 int NOTE_PCTRLMASK ; 
 int PDF_EXITED ; 

__attribute__((used)) static int
procdesc_kqops_event(struct knote *kn, long hint)
{
	struct procdesc *pd;
	u_int event;

	pd = kn->kn_fp->f_data;
	if (hint == 0) {
		/*
		 * Initial test after registration. Generate a NOTE_EXIT in
		 * case the process already terminated before registration.
		 */
		event = pd->pd_flags & PDF_EXITED ? NOTE_EXIT : 0;
	} else {
		/* Mask off extra data. */
		event = (u_int)hint & NOTE_PCTRLMASK;
	}

	/* If the user is interested in this event, record it. */
	if (kn->kn_sfflags & event)
		kn->kn_fflags |= event;

	/* Process is gone, so flag the event as finished. */
	if (event == NOTE_EXIT) {
		kn->kn_flags |= EV_EOF | EV_ONESHOT;
		if (kn->kn_fflags & NOTE_EXIT)
			kn->kn_data = pd->pd_xstat;
		if (kn->kn_fflags == 0)
			kn->kn_flags |= EV_DROP;
		return (1);
	}

	return (kn->kn_fflags != 0);
}