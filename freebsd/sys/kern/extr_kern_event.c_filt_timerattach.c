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
struct kq_timer_cb_data {int /*<<< orphan*/  c; } ;
struct TYPE_2__ {struct kq_timer_cb_data* p_v; } ;
struct knote {int kn_sfflags; TYPE_1__ kn_ptr; int /*<<< orphan*/  kn_status; int /*<<< orphan*/  kn_flags; } ;
typedef  int /*<<< orphan*/  sbintime_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EV_CLEAR ; 
 int /*<<< orphan*/  KN_DETACHED ; 
 int /*<<< orphan*/  M_KQUEUE ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int NOTE_ABSTIME ; 
 int /*<<< orphan*/  atomic_cmpset_int (unsigned int*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  filt_timerstart (struct knote*,int /*<<< orphan*/ ) ; 
 int filt_timervalidate (struct knote*,int /*<<< orphan*/ *) ; 
 unsigned int kq_calloutmax ; 
 unsigned int kq_ncallouts ; 
 struct kq_timer_cb_data* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
filt_timerattach(struct knote *kn)
{
	struct kq_timer_cb_data *kc;
	sbintime_t to;
	unsigned int ncallouts;
	int error;

	error = filt_timervalidate(kn, &to);
	if (error != 0)
		return (error);

	do {
		ncallouts = kq_ncallouts;
		if (ncallouts >= kq_calloutmax)
			return (ENOMEM);
	} while (!atomic_cmpset_int(&kq_ncallouts, ncallouts, ncallouts + 1));

	if ((kn->kn_sfflags & NOTE_ABSTIME) == 0)
		kn->kn_flags |= EV_CLEAR;	/* automatically set */
	kn->kn_status &= ~KN_DETACHED;		/* knlist_add clears it */
	kn->kn_ptr.p_v = kc = malloc(sizeof(*kc), M_KQUEUE, M_WAITOK);
	callout_init(&kc->c, 1);
	filt_timerstart(kn, to);

	return (0);
}