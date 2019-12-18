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
typedef  int uint8_t ;
struct tcphdr {int th_flags; } ;
struct tcpcb {int t_flags; TYPE_1__* ccv; int /*<<< orphan*/  t_inpcb; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* ecnpkt_handler ) (TYPE_1__*) ;} ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int CCF_ACKNOW ; 
 int CCF_DELACK ; 
 int CCF_IPHDR_CE ; 
 int CCF_TCPHDR_CWR ; 
 TYPE_2__* CC_ALGO (struct tcpcb*) ; 
 int /*<<< orphan*/  INP_WLOCK_ASSERT (int /*<<< orphan*/ ) ; 
#define  IPTOS_ECN_CE 130 
#define  IPTOS_ECN_ECT0 129 
#define  IPTOS_ECN_ECT1 128 
 int IPTOS_ECN_MASK ; 
 int TF_DELACK ; 
 int TH_CWR ; 
 int /*<<< orphan*/  TT_DELACK ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  tcp_delacktime ; 
 int /*<<< orphan*/  tcp_timer_activate (struct tcpcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void inline
cc_ecnpkt_handler(struct tcpcb *tp, struct tcphdr *th, uint8_t iptos)
{
	INP_WLOCK_ASSERT(tp->t_inpcb);

	if (CC_ALGO(tp)->ecnpkt_handler != NULL) {
		switch (iptos & IPTOS_ECN_MASK) {
		case IPTOS_ECN_CE:
		    tp->ccv->flags |= CCF_IPHDR_CE;
		    break;
		case IPTOS_ECN_ECT0:
		    tp->ccv->flags &= ~CCF_IPHDR_CE;
		    break;
		case IPTOS_ECN_ECT1:
		    tp->ccv->flags &= ~CCF_IPHDR_CE;
		    break;
		}

		if (th->th_flags & TH_CWR)
			tp->ccv->flags |= CCF_TCPHDR_CWR;
		else
			tp->ccv->flags &= ~CCF_TCPHDR_CWR;

		if (tp->t_flags & TF_DELACK)
			tp->ccv->flags |= CCF_DELACK;
		else
			tp->ccv->flags &= ~CCF_DELACK;

		CC_ALGO(tp)->ecnpkt_handler(tp->ccv);

		if (tp->ccv->flags & CCF_ACKNOW)
			tcp_timer_activate(tp, TT_DELACK, tcp_delacktime);
	}
}