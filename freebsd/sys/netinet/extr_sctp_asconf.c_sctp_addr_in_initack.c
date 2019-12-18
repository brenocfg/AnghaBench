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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int uint16_t ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct sockaddr {int sa_family; } ;
struct sctp_paramhdr {int /*<<< orphan*/  param_length; int /*<<< orphan*/  param_type; } ;
struct sctp_ipv6addr_param {int /*<<< orphan*/  addr; } ;
struct sctp_ipv4addr_param {int /*<<< orphan*/  addr; } ;
struct mbuf {int dummy; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
#define  AF_INET 131 
#define  AF_INET6 130 
 int /*<<< orphan*/  IN6_IS_SCOPE_LINKLOCAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCTPDBG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SCTPDBG_ADDR (int /*<<< orphan*/ ,struct sockaddr*) ; 
 int /*<<< orphan*/  SCTP_DEBUG_ASCONF1 ; 
 int /*<<< orphan*/  SCTP_DEBUG_ASCONF2 ; 
#define  SCTP_IPV4_ADDRESS 129 
#define  SCTP_IPV6_ADDRESS 128 
 scalar_t__ SCTP_SIZE32 (int) ; 
 int /*<<< orphan*/  in6_clearscope (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (struct sockaddr_in6*,struct sockaddr_in6*,int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ sctp_m_getptr (struct mbuf*,scalar_t__,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint32_t
sctp_addr_in_initack(struct mbuf *m, uint32_t offset, uint32_t length, struct sockaddr *sa)
{
	struct sctp_paramhdr tmp_param, *ph;
	uint16_t plen, ptype;
#ifdef INET
	struct sockaddr_in *sin;
	struct sctp_ipv4addr_param *a4p;
	struct sctp_ipv6addr_param addr4_store;
#endif
#ifdef INET6
	struct sockaddr_in6 *sin6;
	struct sctp_ipv6addr_param *a6p;
	struct sctp_ipv6addr_param addr6_store;
	struct sockaddr_in6 sin6_tmp;
#endif

	switch (sa->sa_family) {
#ifdef INET
	case AF_INET:
		break;
#endif
#ifdef INET6
	case AF_INET6:
		break;
#endif
	default:
		return (0);
	}

	SCTPDBG(SCTP_DEBUG_ASCONF2, "find_initack_addr: starting search for ");
	SCTPDBG_ADDR(SCTP_DEBUG_ASCONF2, sa);
	/* convert to upper bound */
	length += offset;

	if ((offset + sizeof(struct sctp_paramhdr)) > length) {
		SCTPDBG(SCTP_DEBUG_ASCONF1,
		    "find_initack_addr: invalid offset?\n");
		return (0);
	}
	/* go through the addresses in the init-ack */
	ph = (struct sctp_paramhdr *)sctp_m_getptr(m, offset,
	    sizeof(struct sctp_paramhdr), (uint8_t *)&tmp_param);
	while (ph != NULL) {
		ptype = ntohs(ph->param_type);
		plen = ntohs(ph->param_length);
		switch (ptype) {
#ifdef INET6
		case SCTP_IPV6_ADDRESS:
			if (sa->sa_family == AF_INET6) {
				/* get the entire IPv6 address param */
				if (plen != sizeof(struct sctp_ipv6addr_param)) {
					break;
				}
				/* get the entire IPv6 address param */
				a6p = (struct sctp_ipv6addr_param *)
				    sctp_m_getptr(m, offset,
				    sizeof(struct sctp_ipv6addr_param),
				    (uint8_t *)&addr6_store);
				if (a6p == NULL) {
					return (0);
				}
				sin6 = (struct sockaddr_in6 *)sa;
				if (IN6_IS_SCOPE_LINKLOCAL(&sin6->sin6_addr)) {
					/* create a copy and clear scope */
					memcpy(&sin6_tmp, sin6,
					    sizeof(struct sockaddr_in6));
					sin6 = &sin6_tmp;
					in6_clearscope(&sin6->sin6_addr);
				}
				if (memcmp(&sin6->sin6_addr, a6p->addr,
				    sizeof(struct in6_addr)) == 0) {
					/* found it */
					return (1);
				}
			}
			break;
#endif				/* INET6 */
#ifdef INET
		case SCTP_IPV4_ADDRESS:
			if (sa->sa_family == AF_INET) {
				if (plen != sizeof(struct sctp_ipv4addr_param)) {
					break;
				}
				/* get the entire IPv4 address param */
				a4p = (struct sctp_ipv4addr_param *)
				    sctp_m_getptr(m, offset,
				    sizeof(struct sctp_ipv4addr_param),
				    (uint8_t *)&addr4_store);
				if (a4p == NULL) {
					return (0);
				}
				sin = (struct sockaddr_in *)sa;
				if (sin->sin_addr.s_addr == a4p->addr) {
					/* found it */
					return (1);
				}
			}
			break;
#endif
		default:
			break;
		}
		/* get next parameter */
		offset += SCTP_SIZE32(plen);
		if (offset + sizeof(struct sctp_paramhdr) > length) {
			return (0);
		}
		ph = (struct sctp_paramhdr *)
		    sctp_m_getptr(m, offset, sizeof(struct sctp_paramhdr),
		    (uint8_t *)&tmp_param);
	}			/* while */
	/* not found! */
	return (0);
}