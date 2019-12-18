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
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in6 {int sin_len; int sin6_len; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_family; TYPE_2__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
union sctp_sockstore {struct sockaddr_in6 sin6; struct sockaddr_in6 sin; struct sockaddr sa; } ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct sockaddr_in {int sin_len; int sin6_len; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_family; TYPE_2__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sctp_tcb {int /*<<< orphan*/  rport; } ;
struct sctp_paramhdr {int /*<<< orphan*/  param_length; int /*<<< orphan*/  param_type; } ;
struct sctp_ipv6addr_param {int /*<<< orphan*/  addr; } ;
struct sctp_ipv4addr_param {int /*<<< orphan*/  addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  param_length; } ;
struct sctp_asconf_paramhdr {int /*<<< orphan*/  correlation_id; TYPE_1__ ph; } ;
struct mbuf {int dummy; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  IN6_IS_ADDR_UNSPECIFIED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  SCTPDBG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SCTPDBG_ADDR (int /*<<< orphan*/ ,struct sockaddr*) ; 
 scalar_t__ SCTP_BASE_SYSCTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_CAUSE_DELETING_LAST_ADDR ; 
 int /*<<< orphan*/  SCTP_CAUSE_DELETING_SRC_ADDR ; 
 int /*<<< orphan*/  SCTP_CAUSE_REQUEST_REFUSED ; 
 int /*<<< orphan*/  SCTP_CAUSE_UNRESOLVABLE_ADDR ; 
 int /*<<< orphan*/  SCTP_DEBUG_ASCONF1 ; 
#define  SCTP_IPV4_ADDRESS 129 
#define  SCTP_IPV6_ADDRESS 128 
 int /*<<< orphan*/  SCTP_NOTIFY_ASCONF_DELETE_IP ; 
 int /*<<< orphan*/  SCTP_SO_NOT_LOCKED ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in6*,int /*<<< orphan*/ ,int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int sctp_asconf_del_remote_addrs_except (struct sctp_tcb*,struct sockaddr*) ; 
 struct mbuf* sctp_asconf_error_response (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct mbuf* sctp_asconf_success_response (int /*<<< orphan*/ ) ; 
 scalar_t__ sctp_cmpaddr (struct sockaddr*,struct sockaddr*) ; 
 int sctp_del_remote_addr (struct sctp_tcb*,struct sockaddr*) ; 
 int /*<<< orphan*/  sctp_nat_friendly ; 
 int /*<<< orphan*/  sctp_ulp_notify (int /*<<< orphan*/ ,struct sctp_tcb*,int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mbuf *
sctp_process_asconf_delete_ip(struct sockaddr *src,
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
	int result;
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
		if (sin->sin_addr.s_addr == INADDR_ANY)
			zero_address = 1;
		SCTPDBG(SCTP_DEBUG_ASCONF1,
		    "process_asconf_delete_ip: deleting ");
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
		memcpy(&sin6->sin6_addr, v6addr->addr,
		    sizeof(struct in6_addr));
		if (IN6_IS_ADDR_UNSPECIFIED(&sin6->sin6_addr))
			zero_address = 1;
		SCTPDBG(SCTP_DEBUG_ASCONF1,
		    "process_asconf_delete_ip: deleting ");
		SCTPDBG_ADDR(SCTP_DEBUG_ASCONF1, sa);
		break;
#endif
	default:
		m_reply = sctp_asconf_error_response(aph->correlation_id,
		    SCTP_CAUSE_UNRESOLVABLE_ADDR, (uint8_t *)aph,
		    aparam_length);
		return (m_reply);
	}

	/* make sure the source address is not being deleted */
	if (sctp_cmpaddr(sa, src)) {
		/* trying to delete the source address! */
		SCTPDBG(SCTP_DEBUG_ASCONF1, "process_asconf_delete_ip: tried to delete source addr\n");
		m_reply = sctp_asconf_error_response(aph->correlation_id,
		    SCTP_CAUSE_DELETING_SRC_ADDR, (uint8_t *)aph,
		    aparam_length);
		return (m_reply);
	}

	/* if deleting 0.0.0.0/::0, delete all addresses except src addr */
	if (zero_address && SCTP_BASE_SYSCTL(sctp_nat_friendly)) {
		result = sctp_asconf_del_remote_addrs_except(stcb, src);

		if (result) {
			/* src address did not exist? */
			SCTPDBG(SCTP_DEBUG_ASCONF1, "process_asconf_delete_ip: src addr does not exist?\n");
			/* what error to reply with?? */
			m_reply =
			    sctp_asconf_error_response(aph->correlation_id,
			    SCTP_CAUSE_REQUEST_REFUSED, (uint8_t *)aph,
			    aparam_length);
		} else if (response_required) {
			m_reply =
			    sctp_asconf_success_response(aph->correlation_id);
		}
		return (m_reply);
	}

	/* delete the address */
	result = sctp_del_remote_addr(stcb, sa);
	/*
	 * note if result == -2, the address doesn't exist in the asoc but
	 * since it's being deleted anyways, we just ack the delete -- but
	 * this probably means something has already gone awry
	 */
	if (result == -1) {
		/* only one address in the asoc */
		SCTPDBG(SCTP_DEBUG_ASCONF1, "process_asconf_delete_ip: tried to delete last IP addr!\n");
		m_reply = sctp_asconf_error_response(aph->correlation_id,
		    SCTP_CAUSE_DELETING_LAST_ADDR, (uint8_t *)aph,
		    aparam_length);
	} else {
		if (response_required) {
			m_reply = sctp_asconf_success_response(aph->correlation_id);
		}
		/* notify upper layer */
		sctp_ulp_notify(SCTP_NOTIFY_ASCONF_DELETE_IP, stcb, 0, sa, SCTP_SO_NOT_LOCKED);
	}
	return (m_reply);
}