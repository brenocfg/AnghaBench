#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_10__ {scalar_t__ th_thread; int /*<<< orphan*/  th_tid; TYPE_2__ const* th_ta; } ;
typedef  TYPE_1__ td_thrhandle_t ;
struct TYPE_11__ {scalar_t__ thread_off_event_buf; scalar_t__ thread_off_tid; int /*<<< orphan*/  ph; int /*<<< orphan*/  thread_last_event_addr; } ;
typedef  TYPE_2__ const td_thragent_t ;
typedef  scalar_t__ td_thr_events_e ;
struct TYPE_12__ {scalar_t__ event; scalar_t__ th_p; } ;
typedef  TYPE_3__ td_event_msg_t ;
typedef  int /*<<< orphan*/  td_err_e ;
typedef  scalar_t__ psaddr_t ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  P2T (int) ; 
 int /*<<< orphan*/  TDBG_FUNC () ; 
 int /*<<< orphan*/  TD_ERR ; 
 int /*<<< orphan*/  TD_NOMSG ; 
 int ps_pread (int /*<<< orphan*/ ,scalar_t__,TYPE_3__*,int) ; 
 int /*<<< orphan*/  ps_pwrite (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int) ; 
 int thr_pread_long (TYPE_2__ const*,scalar_t__,int /*<<< orphan*/ *) ; 
 int thr_pread_ptr (TYPE_2__ const*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  thr_pwrite_ptr (TYPE_2__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static td_err_e
pt_thr_event_getmsg(const td_thrhandle_t *th, td_event_msg_t *msg)
{
	static td_thrhandle_t handle;
	const td_thragent_t *ta = th->th_ta;
	psaddr_t pt, pt_temp;
	int64_t lwp;
	int ret;
	td_thr_events_e	tmp;

	TDBG_FUNC();
	pt = th->th_thread;
	ret = thr_pread_ptr(ta, ta->thread_last_event_addr, &pt_temp);
	if (ret != 0)
		return (TD_ERR);
	/* Get event */
	ret = ps_pread(ta->ph, pt + ta->thread_off_event_buf, msg, sizeof(*msg));
	if (ret != 0)
		return (P2T(ret));
	if (msg->event == 0)
		return (TD_NOMSG);
	/*
	 * Take the event pointer, at the time, libthr only reports event
	 * once a time, so it is not a link list.
	 */
	if (pt == pt_temp)
		thr_pwrite_ptr(ta, ta->thread_last_event_addr, 0);

	/* Clear event */
	tmp = 0;
	ps_pwrite(ta->ph, pt + ta->thread_off_event_buf, &tmp, sizeof(tmp));
	/* Convert event */
	pt = msg->th_p;
	ret = thr_pread_long(ta, pt + ta->thread_off_tid, &lwp);
	if (ret != 0)
		return (TD_ERR);
	handle.th_ta = ta;
	handle.th_tid = lwp;
	handle.th_thread = pt;
	msg->th_p = (uintptr_t)&handle;
	return (0);
}