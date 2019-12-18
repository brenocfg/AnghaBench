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
typedef  int uint32_t ;
struct tcp_hpts_entry {scalar_t__ p_hpts_active; scalar_t__ p_on_min_sleep; void* p_inp; size_t p_nxt_slot; size_t p_runningtick; int p_direct_wake; int /*<<< orphan*/ * p_hptss; int /*<<< orphan*/  p_prev_slot; scalar_t__ p_wheel_complete; } ;
struct inpcb {scalar_t__ inp_in_hpts; size_t inp_hptsslot; scalar_t__ inp_hpts_request; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  HPTS_MTX_ASSERT (struct tcp_hpts_entry*) ; 
 int /*<<< orphan*/  hpts_sane_pace_insert (struct tcp_hpts_entry*,struct inpcb*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t hpts_tick (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcp_wakehpts (struct tcp_hpts_entry*) ; 

__attribute__((used)) static int
tcp_queue_to_hpts_immediate_locked(struct inpcb *inp, struct tcp_hpts_entry *hpts, int32_t line, int32_t noref)
{
	uint32_t need_wake = 0;
	
	HPTS_MTX_ASSERT(hpts);
	if (inp->inp_in_hpts == 0) {
		/* Ok we need to set it on the hpts in the current slot */
		inp->inp_hpts_request = 0;
		if ((hpts->p_hpts_active == 0) ||
		    (hpts->p_wheel_complete)) {
			/*
			 * A sleeping hpts we want in next slot to run 
			 * note that in this state p_prev_slot == p_cur_slot
			 */
			inp->inp_hptsslot = hpts_tick(hpts->p_prev_slot, 1);
			if ((hpts->p_on_min_sleep == 0) && (hpts->p_hpts_active == 0))
				need_wake = 1;
		} else if ((void *)inp == hpts->p_inp) {
			/*
			 * The hpts system is running and the caller
			 * was awoken by the hpts system. 
			 * We can't allow you to go into the same slot we
			 * are in (we don't want a loop :-D).
			 */
			inp->inp_hptsslot = hpts->p_nxt_slot;
		} else
			inp->inp_hptsslot = hpts->p_runningtick;
		hpts_sane_pace_insert(hpts, inp, &hpts->p_hptss[inp->inp_hptsslot], line, noref);
		if (need_wake) {
			/*
			 * Activate the hpts if it is sleeping and its
			 * timeout is not 1.
			 */
			hpts->p_direct_wake = 1;
			tcp_wakehpts(hpts);
		}
	}
	return (need_wake);
}