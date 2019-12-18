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
struct tcpcb {int t_state; } ;
struct tcp_rack {int r_state; int /*<<< orphan*/  r_substate; } ;

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
 int /*<<< orphan*/  rack_do_close_wait ; 
 int /*<<< orphan*/  rack_do_closing ; 
 int /*<<< orphan*/  rack_do_established ; 
 int /*<<< orphan*/  rack_do_fin_wait_1 ; 
 int /*<<< orphan*/  rack_do_fin_wait_2 ; 
 int /*<<< orphan*/  rack_do_lastack ; 
 int /*<<< orphan*/  rack_do_syn_recv ; 
 int /*<<< orphan*/  rack_do_syn_sent ; 
 int /*<<< orphan*/  rack_set_pace_segments (struct tcpcb*,struct tcp_rack*) ; 

__attribute__((used)) static void
rack_set_state(struct tcpcb *tp, struct tcp_rack *rack)
{
	switch (tp->t_state) {
	case TCPS_SYN_SENT:
		rack->r_state = TCPS_SYN_SENT;
		rack->r_substate = rack_do_syn_sent;
		break;
	case TCPS_SYN_RECEIVED:
		rack->r_state = TCPS_SYN_RECEIVED;
		rack->r_substate = rack_do_syn_recv;
		break;
	case TCPS_ESTABLISHED:
		rack_set_pace_segments(tp, rack);
		rack->r_state = TCPS_ESTABLISHED;
		rack->r_substate = rack_do_established;
		break;
	case TCPS_CLOSE_WAIT:
		rack->r_state = TCPS_CLOSE_WAIT;
		rack->r_substate = rack_do_close_wait;
		break;
	case TCPS_FIN_WAIT_1:
		rack->r_state = TCPS_FIN_WAIT_1;
		rack->r_substate = rack_do_fin_wait_1;
		break;
	case TCPS_CLOSING:
		rack->r_state = TCPS_CLOSING;
		rack->r_substate = rack_do_closing;
		break;
	case TCPS_LAST_ACK:
		rack->r_state = TCPS_LAST_ACK;
		rack->r_substate = rack_do_lastack;
		break;
	case TCPS_FIN_WAIT_2:
		rack->r_state = TCPS_FIN_WAIT_2;
		rack->r_substate = rack_do_fin_wait_2;
		break;
	case TCPS_LISTEN:
	case TCPS_CLOSED:
	case TCPS_TIME_WAIT:
	default:
		break;
	};
}