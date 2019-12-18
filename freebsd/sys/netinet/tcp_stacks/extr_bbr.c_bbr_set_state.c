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
typedef  int /*<<< orphan*/  uint32_t ;
struct tcpcb {int t_state; } ;
struct TYPE_3__ {int /*<<< orphan*/  rc_init_rwnd; } ;
struct tcp_bbr {int r_state; int /*<<< orphan*/  r_substate; TYPE_2__* rc_tp; TYPE_1__ r_ctl; } ;
struct TYPE_4__ {int /*<<< orphan*/  snd_wnd; } ;

/* Variables and functions */
#define  TCPS_CLOSED 138 
#define  TCPS_CLOSE_WAIT 137 
#define  TCPS_CLOSING 136 
#define  TCPS_ESTABLISHED 135 
#define  TCPS_FIN_WAIT_1 134 
#define  TCPS_FIN_WAIT_2 133 
#define  TCPS_LAST_ACK 132 
#define  TCPS_LISTEN 131 
#define  TCPS_SYN_RECEIVED 130 
#define  TCPS_SYN_SENT 129 
#define  TCPS_TIME_WAIT 128 
 int /*<<< orphan*/  bbr_do_close_wait ; 
 int /*<<< orphan*/  bbr_do_closing ; 
 int /*<<< orphan*/  bbr_do_established ; 
 int /*<<< orphan*/  bbr_do_fin_wait_1 ; 
 int /*<<< orphan*/  bbr_do_fin_wait_2 ; 
 int /*<<< orphan*/  bbr_do_lastack ; 
 int /*<<< orphan*/  bbr_do_syn_recv ; 
 int /*<<< orphan*/  bbr_do_syn_sent ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bbr_set_state(struct tcpcb *tp, struct tcp_bbr *bbr, uint32_t win)
{
	switch (tp->t_state) {
	case TCPS_SYN_SENT:
		bbr->r_state = TCPS_SYN_SENT;
		bbr->r_substate = bbr_do_syn_sent;
		break;
	case TCPS_SYN_RECEIVED:
		bbr->r_state = TCPS_SYN_RECEIVED;
		bbr->r_substate = bbr_do_syn_recv;
		break;
	case TCPS_ESTABLISHED:
		bbr->r_ctl.rc_init_rwnd = max(win, bbr->rc_tp->snd_wnd);
		bbr->r_state = TCPS_ESTABLISHED;
		bbr->r_substate = bbr_do_established;
		break;
	case TCPS_CLOSE_WAIT:
		bbr->r_state = TCPS_CLOSE_WAIT;
		bbr->r_substate = bbr_do_close_wait;
		break;
	case TCPS_FIN_WAIT_1:
		bbr->r_state = TCPS_FIN_WAIT_1;
		bbr->r_substate = bbr_do_fin_wait_1;
		break;
	case TCPS_CLOSING:
		bbr->r_state = TCPS_CLOSING;
		bbr->r_substate = bbr_do_closing;
		break;
	case TCPS_LAST_ACK:
		bbr->r_state = TCPS_LAST_ACK;
		bbr->r_substate = bbr_do_lastack;
		break;
	case TCPS_FIN_WAIT_2:
		bbr->r_state = TCPS_FIN_WAIT_2;
		bbr->r_substate = bbr_do_fin_wait_2;
		break;
	case TCPS_LISTEN:
	case TCPS_CLOSED:
	case TCPS_TIME_WAIT:
	default:
		break;
	};
}