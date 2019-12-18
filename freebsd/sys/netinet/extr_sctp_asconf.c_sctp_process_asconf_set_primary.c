#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in6 {int sin_len; int sin6_len; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_family; TYPE_2__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
union sctp_sockstore {struct sockaddr_in6 sin6; struct sockaddr_in6 sin; struct sockaddr sa; } ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct sockaddr_in {int sin_len; int sin6_len; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_family; TYPE_2__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct TYPE_7__ {int /*<<< orphan*/  deleted_primary; TYPE_4__* primary_destination; int /*<<< orphan*/ * alternate; } ;
struct sctp_tcb {TYPE_3__ asoc; int /*<<< orphan*/  sctp_ep; } ;
struct sctp_paramhdr {int /*<<< orphan*/  param_length; int /*<<< orphan*/  param_type; } ;
struct sctp_ipv6addr_param {int /*<<< orphan*/  addr; } ;
struct sctp_ipv4addr_param {int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  param_length; } ;
struct sctp_asconf_paramhdr {int /*<<< orphan*/  correlation_id; TYPE_1__ ph; } ;
struct mbuf {int dummy; } ;
struct in6_addr {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_8__ {int dest_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  IN6_IS_ADDR_UNSPECIFIED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  SCTPDBG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SCTPDBG_ADDR (int /*<<< orphan*/ ,struct sockaddr*) ; 
 int SCTP_ADDR_PF ; 
 int SCTP_ADDR_REACHABLE ; 
 int SCTP_ADDR_UNCONFIRMED ; 
 scalar_t__ SCTP_BASE_SYSCTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_CAUSE_UNRESOLVABLE_ADDR ; 
 int /*<<< orphan*/  SCTP_DEBUG_ASCONF1 ; 
 scalar_t__ SCTP_FROM_SCTP_ASCONF ; 
#define  SCTP_IPV4_ADDRESS 129 
#define  SCTP_IPV6_ADDRESS 128 
 scalar_t__ SCTP_LOC_1 ; 
 int /*<<< orphan*/  SCTP_MOBILITY_BASE ; 
 int /*<<< orphan*/  SCTP_MOBILITY_FASTHANDOFF ; 
 int /*<<< orphan*/  SCTP_MOBILITY_PRIM_DELETED ; 
 int /*<<< orphan*/  SCTP_NOTIFY_ASCONF_SET_PRIMARY ; 
 int /*<<< orphan*/  SCTP_SO_NOT_LOCKED ; 
 int /*<<< orphan*/  SCTP_TIMER_TYPE_PRIM_DELETED ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in6*,int /*<<< orphan*/ ,int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 struct mbuf* sctp_asconf_error_response (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct mbuf* sctp_asconf_success_response (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_assoc_immediate_retrans (struct sctp_tcb*,TYPE_4__*) ; 
 int /*<<< orphan*/  sctp_delete_prim_timer (int /*<<< orphan*/ ,struct sctp_tcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_free_remote_addr (int /*<<< orphan*/ *) ; 
 scalar_t__ sctp_is_mobility_feature_on (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_move_chunks_from_net (struct sctp_tcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_nat_friendly ; 
 scalar_t__ sctp_set_primary_addr (struct sctp_tcb*,struct sockaddr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_timer_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sctp_tcb*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sctp_ulp_notify (int /*<<< orphan*/ ,struct sctp_tcb*,int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mbuf *
sctp_process_asconf_set_primary(struct sockaddr *src,
    struct sctp_asconf_paramhdr *aph,
    struct sctp_tcb *stcb, int response_required)
{
	struct mbuf *m_reply = NULL;
	union sctp_sockstore store;
	struct sctp_paramhdr *ph;
	uint16_t param_type, aparam_length;
#if defined(INET) || defined(INET6)
	uint16_t param_length;
#endif
	struct sockaddr *sa;
	int zero_address = 0;
#ifdef INET
	struct sockaddr_in *sin;
	struct sctp_ipv4addr_param *v4addr;
#endif
#ifdef INET6
	struct sockaddr_in6 *sin6;
	struct sctp_ipv6addr_param *v6addr;
#endif

	aparam_length = ntohs(aph->ph.param_length);
	if (aparam_length < sizeof(struct sctp_asconf_paramhdr) + sizeof(struct sctp_paramhdr)) {
		return (NULL);
	}
	ph = (struct sctp_paramhdr *)(aph + 1);
	param_type = ntohs(ph->param_type);
#if defined(INET) || defined(INET6)
	param_length = ntohs(ph->param_length);
	if (param_length + sizeof(struct sctp_asconf_paramhdr) != aparam_length) {
		return (NULL);
	}
#endif
	sa = &store.sa;
	switch (param_type) {
#ifdef INET
	case SCTP_IPV4_ADDRESS:
		if (param_length != sizeof(struct sctp_ipv4addr_param)) {
			/* invalid param size */
			return (NULL);
		}
		v4addr = (struct sctp_ipv4addr_param *)ph;
		sin = &store.sin;
		memset(sin, 0, sizeof(*sin));
		sin->sin_family = AF_INET;
		sin->sin_len = sizeof(struct sockaddr_in);
		sin->sin_addr.s_addr = v4addr->addr;
		if (sin->sin_addr.s_addr == INADDR_ANY)
			zero_address = 1;
		SCTPDBG(SCTP_DEBUG_ASCONF1, "process_asconf_set_primary: ");
		SCTPDBG_ADDR(SCTP_DEBUG_ASCONF1, sa);
		break;
#endif
#ifdef INET6
	case SCTP_IPV6_ADDRESS:
		if (param_length != sizeof(struct sctp_ipv6addr_param)) {
			/* invalid param size */
			return (NULL);
		}
		v6addr = (struct sctp_ipv6addr_param *)ph;
		sin6 = &store.sin6;
		memset(sin6, 0, sizeof(*sin6));
		sin6->sin6_family = AF_INET6;
		sin6->sin6_len = sizeof(struct sockaddr_in6);
		memcpy((caddr_t)&sin6->sin6_addr, v6addr->addr,
		    sizeof(struct in6_addr));
		if (IN6_IS_ADDR_UNSPECIFIED(&sin6->sin6_addr))
			zero_address = 1;
		SCTPDBG(SCTP_DEBUG_ASCONF1, "process_asconf_set_primary: ");
		SCTPDBG_ADDR(SCTP_DEBUG_ASCONF1, sa);
		break;
#endif
	default:
		m_reply = sctp_asconf_error_response(aph->correlation_id,
		    SCTP_CAUSE_UNRESOLVABLE_ADDR, (uint8_t *)aph,
		    aparam_length);
		return (m_reply);
	}

	/* if 0.0.0.0/::0, use the source address instead */
	if (zero_address && SCTP_BASE_SYSCTL(sctp_nat_friendly)) {
		sa = src;
		SCTPDBG(SCTP_DEBUG_ASCONF1,
		    "process_asconf_set_primary: using source addr ");
		SCTPDBG_ADDR(SCTP_DEBUG_ASCONF1, src);
	}
	/* set the primary address */
	if (sctp_set_primary_addr(stcb, sa, NULL) == 0) {
		SCTPDBG(SCTP_DEBUG_ASCONF1,
		    "process_asconf_set_primary: primary address set\n");
		/* notify upper layer */
		sctp_ulp_notify(SCTP_NOTIFY_ASCONF_SET_PRIMARY, stcb, 0, sa, SCTP_SO_NOT_LOCKED);
		if ((stcb->asoc.primary_destination->dest_state & SCTP_ADDR_REACHABLE) &&
		    (!(stcb->asoc.primary_destination->dest_state & SCTP_ADDR_PF)) &&
		    (stcb->asoc.alternate)) {
			sctp_free_remote_addr(stcb->asoc.alternate);
			stcb->asoc.alternate = NULL;
		}
		if (response_required) {
			m_reply = sctp_asconf_success_response(aph->correlation_id);
		}
		/*
		 * Mobility adaptation. Ideally, when the reception of SET
		 * PRIMARY with DELETE IP ADDRESS of the previous primary
		 * destination, unacknowledged DATA are retransmitted
		 * immediately to the new primary destination for seamless
		 * handover. If the destination is UNCONFIRMED and marked to
		 * REQ_PRIM, The retransmission occur when reception of the
		 * HEARTBEAT-ACK.  (See sctp_handle_heartbeat_ack in
		 * sctp_input.c) Also, when change of the primary
		 * destination, it is better that all subsequent new DATA
		 * containing already queued DATA are transmitted to the new
		 * primary destination. (by micchie)
		 */
		if ((sctp_is_mobility_feature_on(stcb->sctp_ep,
		    SCTP_MOBILITY_BASE) ||
		    sctp_is_mobility_feature_on(stcb->sctp_ep,
		    SCTP_MOBILITY_FASTHANDOFF)) &&
		    sctp_is_mobility_feature_on(stcb->sctp_ep,
		    SCTP_MOBILITY_PRIM_DELETED) &&
		    (stcb->asoc.primary_destination->dest_state &
		    SCTP_ADDR_UNCONFIRMED) == 0) {

			sctp_timer_stop(SCTP_TIMER_TYPE_PRIM_DELETED,
			    stcb->sctp_ep, stcb, NULL,
			    SCTP_FROM_SCTP_ASCONF + SCTP_LOC_1);
			if (sctp_is_mobility_feature_on(stcb->sctp_ep,
			    SCTP_MOBILITY_FASTHANDOFF)) {
				sctp_assoc_immediate_retrans(stcb,
				    stcb->asoc.primary_destination);
			}
			if (sctp_is_mobility_feature_on(stcb->sctp_ep,
			    SCTP_MOBILITY_BASE)) {
				sctp_move_chunks_from_net(stcb,
				    stcb->asoc.deleted_primary);
			}
			sctp_delete_prim_timer(stcb->sctp_ep, stcb,
			    stcb->asoc.deleted_primary);
		}
	} else {
		/* couldn't set the requested primary address! */
		SCTPDBG(SCTP_DEBUG_ASCONF1,
		    "process_asconf_set_primary: set primary failed!\n");
		/* must have been an invalid address, so report */
		m_reply = sctp_asconf_error_response(aph->correlation_id,
		    SCTP_CAUSE_UNRESOLVABLE_ADDR, (uint8_t *)aph,
		    aparam_length);
	}

	return (m_reply);
}