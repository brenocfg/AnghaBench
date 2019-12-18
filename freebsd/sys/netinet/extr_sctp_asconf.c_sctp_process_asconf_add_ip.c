#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in6 {int sin_len; int sin6_len; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_family; TYPE_2__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
union sctp_sockstore {struct sockaddr_in6 sin6; struct sockaddr_in6 sin; struct sockaddr sa; } ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct sockaddr_in {int sin_len; int sin6_len; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_family; TYPE_2__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct TYPE_6__ {int /*<<< orphan*/  port; } ;
struct sctp_tcb {int /*<<< orphan*/  sctp_ep; TYPE_3__ asoc; int /*<<< orphan*/  rport; } ;
struct sctp_paramhdr {int /*<<< orphan*/  param_length; int /*<<< orphan*/  param_type; } ;
struct sctp_nets {int dummy; } ;
struct sctp_ipv6addr_param {int /*<<< orphan*/  addr; } ;
struct sctp_ipv4addr_param {int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  param_length; } ;
struct sctp_asconf_paramhdr {int /*<<< orphan*/  correlation_id; TYPE_1__ ph; } ;
struct mbuf {int dummy; } ;
struct in6_addr {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  IN6_IS_ADDR_MULTICAST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IN6_IS_ADDR_UNSPECIFIED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  INADDR_BROADCAST ; 
 int /*<<< orphan*/  IN_MULTICAST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTPDBG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SCTPDBG_ADDR (int /*<<< orphan*/ ,struct sockaddr*) ; 
 int /*<<< orphan*/  SCTP_ADDR_DYNAMIC_ADDED ; 
 scalar_t__ SCTP_BASE_SYSCTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_CAUSE_INVALID_PARAM ; 
 int /*<<< orphan*/  SCTP_CAUSE_RESOURCE_SHORTAGE ; 
 int /*<<< orphan*/  SCTP_DEBUG_ASCONF1 ; 
 int /*<<< orphan*/  SCTP_DONOT_SETSCOPE ; 
#define  SCTP_IPV4_ADDRESS 129 
#define  SCTP_IPV6_ADDRESS 128 
 int /*<<< orphan*/  SCTP_NOTIFY_ASCONF_ADD_IP ; 
 int /*<<< orphan*/  SCTP_SO_NOT_LOCKED ; 
 int /*<<< orphan*/  SCTP_TIMER_TYPE_HEARTBEAT ; 
 int /*<<< orphan*/  SCTP_TIMER_TYPE_PATHMTURAISE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in6*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ sctp_add_remote_addr (struct sctp_tcb*,struct sockaddr*,struct sctp_nets**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mbuf* sctp_asconf_error_response (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct mbuf* sctp_asconf_success_response (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_nat_friendly ; 
 int /*<<< orphan*/  sctp_send_hb (struct sctp_tcb*,struct sctp_nets*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_timer_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sctp_tcb*,struct sctp_nets*) ; 
 int /*<<< orphan*/  sctp_ulp_notify (int /*<<< orphan*/ ,struct sctp_tcb*,int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mbuf *
sctp_process_asconf_add_ip(struct sockaddr *src, struct sctp_asconf_paramhdr *aph,
    struct sctp_tcb *stcb, int send_hb, int response_required)
{
	struct sctp_nets *net;
	struct mbuf *m_reply = NULL;
	union sctp_sockstore store;
	struct sctp_paramhdr *ph;
	uint16_t param_type, aparam_length;
#if defined(INET) || defined(INET6)
	uint16_t param_length;
#endif
	struct sockaddr *sa;
	int zero_address = 0;
	int bad_address = 0;
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
		sin->sin_port = stcb->rport;
		sin->sin_addr.s_addr = v4addr->addr;
		if ((sin->sin_addr.s_addr == INADDR_BROADCAST) ||
		    IN_MULTICAST(ntohl(sin->sin_addr.s_addr))) {
			bad_address = 1;
		}
		if (sin->sin_addr.s_addr == INADDR_ANY)
			zero_address = 1;
		SCTPDBG(SCTP_DEBUG_ASCONF1, "process_asconf_add_ip: adding ");
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
		sin6->sin6_port = stcb->rport;
		memcpy((caddr_t)&sin6->sin6_addr, v6addr->addr,
		    sizeof(struct in6_addr));
		if (IN6_IS_ADDR_MULTICAST(&sin6->sin6_addr)) {
			bad_address = 1;
		}
		if (IN6_IS_ADDR_UNSPECIFIED(&sin6->sin6_addr))
			zero_address = 1;
		SCTPDBG(SCTP_DEBUG_ASCONF1, "process_asconf_add_ip: adding ");
		SCTPDBG_ADDR(SCTP_DEBUG_ASCONF1, sa);
		break;
#endif
	default:
		m_reply = sctp_asconf_error_response(aph->correlation_id,
		    SCTP_CAUSE_INVALID_PARAM, (uint8_t *)aph,
		    aparam_length);
		return (m_reply);
	}			/* end switch */

	/* if 0.0.0.0/::0, add the source address instead */
	if (zero_address && SCTP_BASE_SYSCTL(sctp_nat_friendly)) {
		sa = src;
		SCTPDBG(SCTP_DEBUG_ASCONF1,
		    "process_asconf_add_ip: using source addr ");
		SCTPDBG_ADDR(SCTP_DEBUG_ASCONF1, src);
	}
	net = NULL;
	/* add the address */
	if (bad_address) {
		m_reply = sctp_asconf_error_response(aph->correlation_id,
		    SCTP_CAUSE_INVALID_PARAM, (uint8_t *)aph,
		    aparam_length);
	} else if (sctp_add_remote_addr(stcb, sa, &net, stcb->asoc.port,
		    SCTP_DONOT_SETSCOPE,
	    SCTP_ADDR_DYNAMIC_ADDED) != 0) {
		SCTPDBG(SCTP_DEBUG_ASCONF1,
		    "process_asconf_add_ip: error adding address\n");
		m_reply = sctp_asconf_error_response(aph->correlation_id,
		    SCTP_CAUSE_RESOURCE_SHORTAGE, (uint8_t *)aph,
		    aparam_length);
	} else {
		if (response_required) {
			m_reply =
			    sctp_asconf_success_response(aph->correlation_id);
		}
		if (net != NULL) {
			/* notify upper layer */
			sctp_ulp_notify(SCTP_NOTIFY_ASCONF_ADD_IP, stcb, 0, sa, SCTP_SO_NOT_LOCKED);
			sctp_timer_start(SCTP_TIMER_TYPE_PATHMTURAISE, stcb->sctp_ep, stcb, net);
			sctp_timer_start(SCTP_TIMER_TYPE_HEARTBEAT, stcb->sctp_ep,
			    stcb, net);
			if (send_hb) {
				sctp_send_hb(stcb, net, SCTP_SO_NOT_LOCKED);
			}
		}
	}
	return (m_reply);
}