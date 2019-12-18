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
struct TYPE_4__ {int /*<<< orphan*/  si_note; } ;
struct pipe {TYPE_2__ pipe_sel; TYPE_1__* pipe_peer; } ;
struct knote {int kn_filter; struct pipe* kn_hook; int /*<<< orphan*/ * kn_fop; } ;
struct file {int f_flag; struct pipe* f_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  pipe_present; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPIPE ; 
#define  EVFILT_READ 129 
#define  EVFILT_WRITE 128 
 int FREAD ; 
 int FWRITE ; 
 int /*<<< orphan*/  PIPE_ACTIVE ; 
 int /*<<< orphan*/  PIPE_LOCK (struct pipe*) ; 
 struct pipe* PIPE_PEER (struct pipe*) ; 
 int /*<<< orphan*/  PIPE_UNLOCK (struct pipe*) ; 
 int /*<<< orphan*/  knlist_add (int /*<<< orphan*/ *,struct knote*,int) ; 
 int /*<<< orphan*/  pipe_nfiltops ; 
 int /*<<< orphan*/  pipe_rfiltops ; 
 int /*<<< orphan*/  pipe_wfiltops ; 

__attribute__((used)) static int
pipe_kqfilter(struct file *fp, struct knote *kn)
{
	struct pipe *cpipe;

	/*
	 * If a filter is requested that is not supported by this file
	 * descriptor, don't return an error, but also don't ever generate an
	 * event.
	 */
	if ((kn->kn_filter == EVFILT_READ) && !(fp->f_flag & FREAD)) {
		kn->kn_fop = &pipe_nfiltops;
		return (0);
	}
	if ((kn->kn_filter == EVFILT_WRITE) && !(fp->f_flag & FWRITE)) {
		kn->kn_fop = &pipe_nfiltops;
		return (0);
	}
	cpipe = fp->f_data;
	PIPE_LOCK(cpipe);
	switch (kn->kn_filter) {
	case EVFILT_READ:
		kn->kn_fop = &pipe_rfiltops;
		break;
	case EVFILT_WRITE:
		kn->kn_fop = &pipe_wfiltops;
		if (cpipe->pipe_peer->pipe_present != PIPE_ACTIVE) {
			/* other end of pipe has been closed */
			PIPE_UNLOCK(cpipe);
			return (EPIPE);
		}
		cpipe = PIPE_PEER(cpipe);
		break;
	default:
		PIPE_UNLOCK(cpipe);
		return (EINVAL);
	}

	kn->kn_hook = cpipe; 
	knlist_add(&cpipe->pipe_sel.si_note, kn, 1);
	PIPE_UNLOCK(cpipe);
	return (0);
}