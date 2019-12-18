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
struct tcp_hpts_entry {int dummy; } ;
struct inpcb {int inp_flags2; } ;
typedef  int int32_t ;

/* Variables and functions */
 int INP_FREED ; 
 scalar_t__ __in_pcbrele_wlocked (struct inpcb*,int) ; 
 scalar_t__ in_pcbrele_wlocked (struct inpcb*) ; 
 int /*<<< orphan*/  panic (char*,struct inpcb*) ; 

__attribute__((used)) static void
tcp_remove_hpts_ref(struct inpcb *inp, struct tcp_hpts_entry *hpts, int line)
{
	int32_t add_freed;

	if (inp->inp_flags2 & INP_FREED) {
		/*
		 * Need to play a special trick so that in_pcbrele_wlocked
		 * does not return 1 when it really should have returned 0.
		 */
		add_freed = 1;
		inp->inp_flags2 &= ~INP_FREED;
	} else {
		add_freed = 0;
	}
#ifndef INP_REF_DEBUG
	if (in_pcbrele_wlocked(inp)) {
		/*
		 * This should not happen. We have the inpcb referred to by
		 * the main socket (why we are called) and the hpts. It
		 * should always return 0.
		 */
		panic("inpcb:%p release ret 1",
		    inp);
	}
#else
	if (__in_pcbrele_wlocked(inp, line)) {
		/*
		 * This should not happen. We have the inpcb referred to by
		 * the main socket (why we are called) and the hpts. It
		 * should always return 0.
		 */
		panic("inpcb:%p release ret 1",
		    inp);
	}
#endif
	if (add_freed) {
		inp->inp_flags2 |= INP_FREED;
	}
}