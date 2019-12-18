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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct timeval {int dummy; } ;
struct tcpcb {scalar_t__ t_in_pkt; TYPE_1__* t_fb; int /*<<< orphan*/ * t_fb_ptr; int /*<<< orphan*/ * t_inpcb; } ;
struct tcp_hpts_entry {struct inpcb* p_inp; int /*<<< orphan*/  p_mtx; int /*<<< orphan*/  p_input; } ;
struct inpcb {scalar_t__ inp_input_cpu_set; int inp_flags; int inp_flags2; int /*<<< orphan*/  inp_socket; scalar_t__ inp_in_input; int /*<<< orphan*/  inp_vnet; int /*<<< orphan*/  inp_hpts_drop_reas; } ;
typedef  int int16_t ;
struct TYPE_2__ {int (* tfb_do_queued_segments ) (int /*<<< orphan*/ ,struct tcpcb*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPTS_MTX_ASSERT (struct tcp_hpts_entry*) ; 
 int /*<<< orphan*/  HPTS_REMOVE_INPUT ; 
 int INP_DROPPED ; 
 int INP_FREED ; 
 int INP_SUPPORTS_MBUFQ ; 
 int INP_TIMEWAIT ; 
 int /*<<< orphan*/  INP_UNLOCK_ASSERT (struct inpcb*) ; 
 int /*<<< orphan*/  INP_WLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  INP_WUNLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  NET_EPOCH_ASSERT () ; 
 struct inpcb* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hpts_sane_input_remove (struct tcp_hpts_entry*,struct inpcb*,int /*<<< orphan*/ ) ; 
 scalar_t__ in_pcbrele_wlocked (struct inpcb*) ; 
 struct tcpcb* intotcpcb (struct inpcb*) ; 
 int /*<<< orphan*/  kern_prefetch (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,struct tcpcb*,int /*<<< orphan*/ ) ; 
 struct tcpcb* tcp_drop (struct tcpcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_drop_in_pkts (struct tcpcb*) ; 
 int /*<<< orphan*/  tcp_hpts_remove (struct inpcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_set_hpts (struct inpcb*) ; 

__attribute__((used)) static void
tcp_input_data(struct tcp_hpts_entry *hpts, struct timeval *tv)
{
	struct tcpcb *tp;
	struct inpcb *inp;
	uint16_t drop_reason;
	int16_t set_cpu;
	uint32_t did_prefetch = 0;
	int dropped;

	HPTS_MTX_ASSERT(hpts);
	NET_EPOCH_ASSERT();

	while ((inp = TAILQ_FIRST(&hpts->p_input)) != NULL) {
		HPTS_MTX_ASSERT(hpts);
		hpts_sane_input_remove(hpts, inp, 0);
		if (inp->inp_input_cpu_set == 0) {
			set_cpu = 1;
		} else {
			set_cpu = 0;
		}
		hpts->p_inp = inp;
		drop_reason = inp->inp_hpts_drop_reas;
		inp->inp_in_input = 0;
		mtx_unlock(&hpts->p_mtx);
		INP_WLOCK(inp);
#ifdef VIMAGE
		CURVNET_SET(inp->inp_vnet);
#endif
		if ((inp->inp_flags & (INP_TIMEWAIT | INP_DROPPED)) ||
		    (inp->inp_flags2 & INP_FREED)) {
out:
			hpts->p_inp = NULL;
			if (in_pcbrele_wlocked(inp) == 0) {
				INP_WUNLOCK(inp);
			}
#ifdef VIMAGE
			CURVNET_RESTORE();
#endif
			mtx_lock(&hpts->p_mtx);
			continue;
		}
		tp = intotcpcb(inp);
		if ((tp == NULL) || (tp->t_inpcb == NULL)) {
			goto out;
		}
		if (drop_reason) {
			/* This tcb is being destroyed for drop_reason */
			tcp_drop_in_pkts(tp);
			tp = tcp_drop(tp, drop_reason);
			if (tp == NULL) {
				INP_WLOCK(inp);
			}
			if (in_pcbrele_wlocked(inp) == 0)
				INP_WUNLOCK(inp);
#ifdef VIMAGE
			CURVNET_RESTORE();
#endif
			mtx_lock(&hpts->p_mtx);
			continue;
		}
		if (set_cpu) {
			/*
			 * Setup so the next time we will move to the right
			 * CPU. This should be a rare event. It will
			 * sometimes happens when we are the client side
			 * (usually not the server). Somehow tcp_output()
			 * gets called before the tcp_do_segment() sets the
			 * intial state. This means the r_cpu and r_hpts_cpu
			 * is 0. We get on the hpts, and then tcp_input()
			 * gets called setting up the r_cpu to the correct
			 * value. The hpts goes off and sees the mis-match.
			 * We simply correct it here and the CPU will switch
			 * to the new hpts nextime the tcb gets added to the
			 * the hpts (not this time) :-)
			 */
			tcp_set_hpts(inp);
		}
		if (tp->t_fb_ptr != NULL) {
			kern_prefetch(tp->t_fb_ptr, &did_prefetch);
			did_prefetch = 1;
		}
		if ((inp->inp_flags2 & INP_SUPPORTS_MBUFQ) && tp->t_in_pkt) {
			if (inp->inp_in_input)
				tcp_hpts_remove(inp, HPTS_REMOVE_INPUT);
			dropped = (*tp->t_fb->tfb_do_queued_segments)(inp->inp_socket, tp, 0);
			if (dropped) {
				/* Re-acquire the wlock so we can release the reference */
				INP_WLOCK(inp);
			}
		} else if (tp->t_in_pkt) {
			/* 
			 * We reach here only if we had a 
			 * stack that supported INP_SUPPORTS_MBUFQ
			 * and then somehow switched to a stack that
			 * does not. The packets are basically stranded
			 * and would hang with the connection until
			 * cleanup without this code. Its not the
			 * best way but I know of no other way to
			 * handle it since the stack needs functions
			 * it does not have to handle queued packets.
			 */
			tcp_drop_in_pkts(tp);
		}
		if (in_pcbrele_wlocked(inp) == 0)
			INP_WUNLOCK(inp);
		INP_UNLOCK_ASSERT(inp);
#ifdef VIMAGE
		CURVNET_RESTORE();
#endif
		mtx_lock(&hpts->p_mtx);
		hpts->p_inp = NULL;
	}
}