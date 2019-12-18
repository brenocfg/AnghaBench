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
typedef  int /*<<< orphan*/  u_short ;
struct tcphdr {int th_flags; } ;
struct pf_state_peer {scalar_t__ state; scalar_t__ seqlo; } ;
struct pf_state {int /*<<< orphan*/  timeout; int /*<<< orphan*/  expire; int /*<<< orphan*/ * src_node; } ;
struct TYPE_2__ {struct tcphdr* tcp; } ;
struct pf_pdesc {TYPE_1__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PFRES_SRCLIMIT ; 
 int /*<<< orphan*/  PFTM_TCP_CLOSED ; 
 int /*<<< orphan*/  PFTM_TCP_CLOSING ; 
 int /*<<< orphan*/  PFTM_TCP_ESTABLISHED ; 
 int /*<<< orphan*/  PFTM_TCP_FIN_WAIT ; 
 int /*<<< orphan*/  PFTM_TCP_OPENING ; 
 int PF_DROP ; 
 int PF_PASS ; 
 int /*<<< orphan*/  REASON_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ TCPS_CLOSING ; 
 scalar_t__ TCPS_ESTABLISHED ; 
 scalar_t__ TCPS_FIN_WAIT_2 ; 
 scalar_t__ TCPS_SYN_SENT ; 
 scalar_t__ TCPS_TIME_WAIT ; 
 int TH_ACK ; 
 int TH_FIN ; 
 int TH_RST ; 
 int TH_SYN ; 
 scalar_t__ pf_src_connlimit (struct pf_state**) ; 
 int /*<<< orphan*/  time_uptime ; 

__attribute__((used)) static int
pf_tcp_track_sloppy(struct pf_state_peer *src, struct pf_state_peer *dst,
	struct pf_state **state, struct pf_pdesc *pd, u_short *reason)
{
	struct tcphdr		*th = pd->hdr.tcp;

	if (th->th_flags & TH_SYN)
		if (src->state < TCPS_SYN_SENT)
			src->state = TCPS_SYN_SENT;
	if (th->th_flags & TH_FIN)
		if (src->state < TCPS_CLOSING)
			src->state = TCPS_CLOSING;
	if (th->th_flags & TH_ACK) {
		if (dst->state == TCPS_SYN_SENT) {
			dst->state = TCPS_ESTABLISHED;
			if (src->state == TCPS_ESTABLISHED &&
			    (*state)->src_node != NULL &&
			    pf_src_connlimit(state)) {
				REASON_SET(reason, PFRES_SRCLIMIT);
				return (PF_DROP);
			}
		} else if (dst->state == TCPS_CLOSING) {
			dst->state = TCPS_FIN_WAIT_2;
		} else if (src->state == TCPS_SYN_SENT &&
		    dst->state < TCPS_SYN_SENT) {
			/*
			 * Handle a special sloppy case where we only see one
			 * half of the connection. If there is a ACK after
			 * the initial SYN without ever seeing a packet from
			 * the destination, set the connection to established.
			 */
			dst->state = src->state = TCPS_ESTABLISHED;
			if ((*state)->src_node != NULL &&
			    pf_src_connlimit(state)) {
				REASON_SET(reason, PFRES_SRCLIMIT);
				return (PF_DROP);
			}
		} else if (src->state == TCPS_CLOSING &&
		    dst->state == TCPS_ESTABLISHED &&
		    dst->seqlo == 0) {
			/*
			 * Handle the closing of half connections where we
			 * don't see the full bidirectional FIN/ACK+ACK
			 * handshake.
			 */
			dst->state = TCPS_CLOSING;
		}
	}
	if (th->th_flags & TH_RST)
		src->state = dst->state = TCPS_TIME_WAIT;

	/* update expire time */
	(*state)->expire = time_uptime;
	if (src->state >= TCPS_FIN_WAIT_2 &&
	    dst->state >= TCPS_FIN_WAIT_2)
		(*state)->timeout = PFTM_TCP_CLOSED;
	else if (src->state >= TCPS_CLOSING &&
	    dst->state >= TCPS_CLOSING)
		(*state)->timeout = PFTM_TCP_FIN_WAIT;
	else if (src->state < TCPS_ESTABLISHED ||
	    dst->state < TCPS_ESTABLISHED)
		(*state)->timeout = PFTM_TCP_OPENING;
	else if (src->state >= TCPS_CLOSING ||
	    dst->state >= TCPS_CLOSING)
		(*state)->timeout = PFTM_TCP_CLOSING;
	else
		(*state)->timeout = PFTM_TCP_ESTABLISHED;

	return (PF_PASS);
}