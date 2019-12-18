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
struct tcphdr {int dummy; } ;
struct tcpcb {int /*<<< orphan*/  t_inpcb; scalar_t__ t_fb_ptr; } ;
struct TYPE_2__ {scalar_t__ rc_prr_sndcnt; } ;
struct tcp_rack {int /*<<< orphan*/  r_wanted_output; TYPE_1__ r_ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  INP_WLOCK_ASSERT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tcp_rack_partialack(struct tcpcb *tp, struct tcphdr *th)
{
	struct tcp_rack *rack;

	rack = (struct tcp_rack *)tp->t_fb_ptr;
	INP_WLOCK_ASSERT(tp->t_inpcb);
	if (rack->r_ctl.rc_prr_sndcnt > 0)
		rack->r_wanted_output++;
}