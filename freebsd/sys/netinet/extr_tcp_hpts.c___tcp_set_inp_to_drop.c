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
typedef  int /*<<< orphan*/  uint16_t ;
struct tcpcb {int /*<<< orphan*/  t_inpcb; } ;
struct tcp_hpts_entry {scalar_t__ p_hpts_active; int p_direct_wake; int /*<<< orphan*/  p_mtx; } ;
struct inpcb {scalar_t__ inp_in_input; int /*<<< orphan*/  inp_hpts_drop_reas; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  hpts_sane_input_insert (struct tcp_hpts_entry*,struct inpcb*,int /*<<< orphan*/ ) ; 
 struct tcpcb* intotcpcb (struct inpcb*) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 struct tcp_hpts_entry* tcp_input_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_wakeinput (struct tcp_hpts_entry*) ; 

void
__tcp_set_inp_to_drop(struct inpcb *inp, uint16_t reason, int32_t line)
{
	struct tcp_hpts_entry *hpts;
	struct tcpcb *tp;

	tp = intotcpcb(inp);
	hpts = tcp_input_lock(tp->t_inpcb);
	if (inp->inp_in_input == 0) {
		/* Ok we need to set it on the hpts in the current slot */
		hpts_sane_input_insert(hpts, inp, line);
		if (hpts->p_hpts_active == 0) {
			/*
			 * Activate the hpts if it is sleeping.
			 */
			hpts->p_direct_wake = 1;
			tcp_wakeinput(hpts);
		}
	} else if (hpts->p_hpts_active == 0) {
		hpts->p_direct_wake = 1;
		tcp_wakeinput(hpts);
	}
	inp->inp_hpts_drop_reas = reason;
	mtx_unlock(&hpts->p_mtx);
}