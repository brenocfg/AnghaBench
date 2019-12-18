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
typedef  int /*<<< orphan*/  module_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPL_ABORT_RPL_RSS ; 
 int /*<<< orphan*/  CPL_ACT_OPEN_RPL ; 
 int /*<<< orphan*/  CPL_COOKIE_FILTER ; 
 int /*<<< orphan*/  CPL_COOKIE_HASHFILTER ; 
 int /*<<< orphan*/  CPL_L2T_WRITE_RPL ; 
 int /*<<< orphan*/  CPL_SET_TCB_RPL ; 
 int /*<<< orphan*/  CPL_SMT_WRITE_RPL ; 
 int /*<<< orphan*/  CPL_T5_TRACE_PKT ; 
 int /*<<< orphan*/  CPL_TRACE_PKT ; 
 int EBUSY ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  do_l2t_write_rpl ; 
 int /*<<< orphan*/  do_smt_write_rpl ; 
 int /*<<< orphan*/  fatal_callout ; 
 int hz ; 
 int /*<<< orphan*/  mlu ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sx_slock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_sunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t4_clip_modload () ; 
 int /*<<< orphan*/  t4_clip_modunload () ; 
 int /*<<< orphan*/  t4_del_hashfilter_rpl ; 
 int /*<<< orphan*/  t4_filter_rpl ; 
 int /*<<< orphan*/  t4_hashfilter_ao_rpl ; 
 int /*<<< orphan*/  t4_hashfilter_tcb_rpl ; 
 int /*<<< orphan*/  t4_list ; 
 int /*<<< orphan*/  t4_list_lock ; 
 int /*<<< orphan*/  t4_register_cpl_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_register_shared_cpl_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_sge_extfree_refs () ; 
 int /*<<< orphan*/  t4_sge_modload () ; 
 int /*<<< orphan*/  t4_sge_modunload () ; 
 int /*<<< orphan*/  t4_trace_pkt ; 
 int /*<<< orphan*/  t4_tracer_modload () ; 
 int /*<<< orphan*/  t4_tracer_modunload () ; 
 int /*<<< orphan*/  t4_uld_list ; 
 int /*<<< orphan*/  t4_uld_list_lock ; 
 int /*<<< orphan*/  t5_trace_pkt ; 
 int /*<<< orphan*/  tweak_tunables () ; 
 int /*<<< orphan*/  uprintf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mod_event(module_t mod, int cmd, void *arg)
{
	int rc = 0;
	static int loaded = 0;

	switch (cmd) {
	case MOD_LOAD:
		sx_xlock(&mlu);
		if (loaded++ == 0) {
			t4_sge_modload();
			t4_register_shared_cpl_handler(CPL_SET_TCB_RPL,
			    t4_filter_rpl, CPL_COOKIE_FILTER);
			t4_register_shared_cpl_handler(CPL_L2T_WRITE_RPL,
			    do_l2t_write_rpl, CPL_COOKIE_FILTER);
			t4_register_shared_cpl_handler(CPL_ACT_OPEN_RPL,
			    t4_hashfilter_ao_rpl, CPL_COOKIE_HASHFILTER);
			t4_register_shared_cpl_handler(CPL_SET_TCB_RPL,
			    t4_hashfilter_tcb_rpl, CPL_COOKIE_HASHFILTER);
			t4_register_shared_cpl_handler(CPL_ABORT_RPL_RSS,
			    t4_del_hashfilter_rpl, CPL_COOKIE_HASHFILTER);
			t4_register_cpl_handler(CPL_TRACE_PKT, t4_trace_pkt);
			t4_register_cpl_handler(CPL_T5_TRACE_PKT, t5_trace_pkt);
			t4_register_cpl_handler(CPL_SMT_WRITE_RPL,
			    do_smt_write_rpl);
			sx_init(&t4_list_lock, "T4/T5 adapters");
			SLIST_INIT(&t4_list);
			callout_init(&fatal_callout, 1);
#ifdef TCP_OFFLOAD
			sx_init(&t4_uld_list_lock, "T4/T5 ULDs");
			SLIST_INIT(&t4_uld_list);
#endif
#ifdef INET6
			t4_clip_modload();
#endif
			t4_tracer_modload();
			tweak_tunables();
		}
		sx_xunlock(&mlu);
		break;

	case MOD_UNLOAD:
		sx_xlock(&mlu);
		if (--loaded == 0) {
			int tries;

			sx_slock(&t4_list_lock);
			if (!SLIST_EMPTY(&t4_list)) {
				rc = EBUSY;
				sx_sunlock(&t4_list_lock);
				goto done_unload;
			}
#ifdef TCP_OFFLOAD
			sx_slock(&t4_uld_list_lock);
			if (!SLIST_EMPTY(&t4_uld_list)) {
				rc = EBUSY;
				sx_sunlock(&t4_uld_list_lock);
				sx_sunlock(&t4_list_lock);
				goto done_unload;
			}
#endif
			tries = 0;
			while (tries++ < 5 && t4_sge_extfree_refs() != 0) {
				uprintf("%ju clusters with custom free routine "
				    "still is use.\n", t4_sge_extfree_refs());
				pause("t4unload", 2 * hz);
			}
#ifdef TCP_OFFLOAD
			sx_sunlock(&t4_uld_list_lock);
#endif
			sx_sunlock(&t4_list_lock);

			if (t4_sge_extfree_refs() == 0) {
				t4_tracer_modunload();
#ifdef INET6
				t4_clip_modunload();
#endif
#ifdef TCP_OFFLOAD
				sx_destroy(&t4_uld_list_lock);
#endif
				sx_destroy(&t4_list_lock);
				t4_sge_modunload();
				loaded = 0;
			} else {
				rc = EBUSY;
				loaded++;	/* undo earlier decrement */
			}
		}
done_unload:
		sx_xunlock(&mlu);
		break;
	}

	return (rc);
}