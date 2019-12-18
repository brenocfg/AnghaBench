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
struct tcpcb {scalar_t__ t_rxtshift; int /*<<< orphan*/  t_flags; } ;
struct TYPE_3__ {scalar_t__ rc_went_idle_time; scalar_t__ rc_hpts_flags; } ;
struct tcp_rack {TYPE_1__ r_ctl; scalar_t__ rc_in_persist; TYPE_2__* rc_inp; } ;
struct TYPE_4__ {scalar_t__ inp_in_hpts; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPTS_REMOVE_OUTPUT ; 
 int /*<<< orphan*/  TF_FORCEDATA ; 
 int /*<<< orphan*/  tcp_hpts_remove (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rack_exit_persist(struct tcpcb *tp, struct tcp_rack *rack)
{
	if (rack->rc_inp->inp_in_hpts)  {
		tcp_hpts_remove(rack->rc_inp, HPTS_REMOVE_OUTPUT);
		rack->r_ctl.rc_hpts_flags  = 0;
	}
	rack->rc_in_persist = 0;
	rack->r_ctl.rc_went_idle_time = 0;
	tp->t_flags &= ~TF_FORCEDATA;
	tp->t_rxtshift = 0;
}