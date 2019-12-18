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
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;
struct tcp_hpts_entry {int p_hpts_active; int p_hpts_sleep_time; int overidden_sleep; int p_on_min_sleep; int /*<<< orphan*/  p_mtx; scalar_t__ p_direct_wake; int /*<<< orphan*/  p_cpu; int /*<<< orphan*/  co; scalar_t__ p_hpts_wake_scheduled; } ;
struct epoch_tracker {int dummy; } ;
typedef  int /*<<< orphan*/  sbintime_t ;

/* Variables and functions */
 int C_DIRECT_EXEC ; 
 int C_PREL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPTS_MTX_ASSERT (struct tcp_hpts_entry*) ; 
 int HPTS_TICKS_PER_USEC ; 
 int /*<<< orphan*/  NET_EPOCH_ENTER (struct epoch_tracker) ; 
 int /*<<< orphan*/  NET_EPOCH_EXIT (struct epoch_tracker) ; 
 int /*<<< orphan*/  callout_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_deactivate (int /*<<< orphan*/ *) ; 
 scalar_t__ callout_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_reset_sbt_on (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tcp_hpts_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hpts_timeout_dir ; 
 int /*<<< orphan*/  hpts_timeout_swi ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ tcp_hpts_callout_skip_swi ; 
 int /*<<< orphan*/  tcp_hpts_precision ; 
 int /*<<< orphan*/  tcp_hptsi (struct tcp_hpts_entry*) ; 
 int tcp_min_hptsi_time ; 
 int /*<<< orphan*/  tvtosbt (struct timeval) ; 

__attribute__((used)) static void
tcp_hpts_thread(void *ctx)
{
	struct tcp_hpts_entry *hpts;
	struct epoch_tracker et;
	struct timeval tv;
	sbintime_t sb;

	hpts = (struct tcp_hpts_entry *)ctx;
	mtx_lock(&hpts->p_mtx);
	if (hpts->p_direct_wake) {
		/* Signaled by input */
		callout_stop(&hpts->co);
	} else {
		/* Timed out */
		if (callout_pending(&hpts->co) ||
		    !callout_active(&hpts->co)) {
			mtx_unlock(&hpts->p_mtx);
			return;
		}
		callout_deactivate(&hpts->co);
	}
	hpts->p_hpts_wake_scheduled = 0;
	hpts->p_hpts_active = 1;
	NET_EPOCH_ENTER(et);
	tcp_hptsi(hpts);
	NET_EPOCH_EXIT(et);
	HPTS_MTX_ASSERT(hpts);
	tv.tv_sec = 0;
	tv.tv_usec = hpts->p_hpts_sleep_time * HPTS_TICKS_PER_USEC;
	if (tcp_min_hptsi_time && (tv.tv_usec < tcp_min_hptsi_time)) {
		hpts->overidden_sleep = tv.tv_usec;
		tv.tv_usec = tcp_min_hptsi_time;
		hpts->p_on_min_sleep = 1;
	} else {
		/* Clear the min sleep flag */
		hpts->overidden_sleep = 0;
		hpts->p_on_min_sleep = 0;
	}
	hpts->p_hpts_active = 0;
	sb = tvtosbt(tv);
	if (tcp_hpts_callout_skip_swi == 0) {
		callout_reset_sbt_on(&hpts->co, sb, 0,
		    hpts_timeout_swi, hpts, hpts->p_cpu,
		    (C_DIRECT_EXEC | C_PREL(tcp_hpts_precision)));
	} else {
		callout_reset_sbt_on(&hpts->co, sb, 0,
		    hpts_timeout_dir, hpts,
		    hpts->p_cpu,
		    C_PREL(tcp_hpts_precision));
	}
	hpts->p_direct_wake = 0;
	mtx_unlock(&hpts->p_mtx);
}