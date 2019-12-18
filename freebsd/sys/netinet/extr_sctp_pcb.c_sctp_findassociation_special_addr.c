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
typedef  scalar_t__ uint16_t ;
struct sockaddr_in6 {int sin_len; int sin6_len; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_family; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr_in {int sin_len; int sin6_len; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_family; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct sctphdr {int /*<<< orphan*/  src_port; } ;
struct sctp_tcb {int dummy; } ;
struct sctp_paramhdr {int /*<<< orphan*/  param_length; int /*<<< orphan*/  param_type; } ;
struct sctp_nets {int dummy; } ;
struct sctp_ipv6addr_param {int /*<<< orphan*/  addr; } ;
struct sctp_ipv4addr_param {int /*<<< orphan*/  addr; } ;
struct sctp_inpcb {int dummy; } ;
struct sctp_init_chunk {int dummy; } ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  sin6 ;
typedef  int /*<<< orphan*/  sin4 ;
typedef  int /*<<< orphan*/  param_buf ;
typedef  int /*<<< orphan*/  ip6_param ;
typedef  int /*<<< orphan*/  ip4_param ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 scalar_t__ SCTP_IPV4_ADDRESS ; 
 scalar_t__ SCTP_IPV6_ADDRESS ; 
 scalar_t__ SCTP_SIZE32 (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in6*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 struct sctp_tcb* sctp_findassociation_ep_addr (struct sctp_inpcb**,struct sockaddr*,struct sctp_nets**,struct sockaddr*,int /*<<< orphan*/ *) ; 
 struct sctp_paramhdr* sctp_get_next_param (struct mbuf*,int,struct sctp_paramhdr*,int) ; 

__attribute__((used)) static struct sctp_tcb *
sctp_findassociation_special_addr(struct mbuf *m, int offset,
    struct sctphdr *sh, struct sctp_inpcb **inp_p, struct sctp_nets **netp,
    struct sockaddr *dst)
{
	struct sctp_paramhdr *phdr, param_buf;
#if defined(INET) || defined(INET6)
	struct sctp_tcb *stcb;
	uint16_t ptype;
#endif
	uint16_t plen;
#ifdef INET
	struct sockaddr_in sin4;
#endif
#ifdef INET6
	struct sockaddr_in6 sin6;
#endif

#ifdef INET
	memset(&sin4, 0, sizeof(sin4));
	sin4.sin_len = sizeof(sin4);
	sin4.sin_family = AF_INET;
	sin4.sin_port = sh->src_port;
#endif
#ifdef INET6
	memset(&sin6, 0, sizeof(sin6));
	sin6.sin6_len = sizeof(sin6);
	sin6.sin6_family = AF_INET6;
	sin6.sin6_port = sh->src_port;
#endif

	offset += sizeof(struct sctp_init_chunk);

	phdr = sctp_get_next_param(m, offset, &param_buf, sizeof(param_buf));
	while (phdr != NULL) {
		/* now we must see if we want the parameter */
#if defined(INET) || defined(INET6)
		ptype = ntohs(phdr->param_type);
#endif
		plen = ntohs(phdr->param_length);
		if (plen == 0) {
			break;
		}
#ifdef INET
		if (ptype == SCTP_IPV4_ADDRESS &&
		    plen == sizeof(struct sctp_ipv4addr_param)) {
			/* Get the rest of the address */
			struct sctp_ipv4addr_param ip4_param, *p4;

			phdr = sctp_get_next_param(m, offset,
			    (struct sctp_paramhdr *)&ip4_param, sizeof(ip4_param));
			if (phdr == NULL) {
				return (NULL);
			}
			p4 = (struct sctp_ipv4addr_param *)phdr;
			memcpy(&sin4.sin_addr, &p4->addr, sizeof(p4->addr));
			/* look it up */
			stcb = sctp_findassociation_ep_addr(inp_p,
			    (struct sockaddr *)&sin4, netp, dst, NULL);
			if (stcb != NULL) {
				return (stcb);
			}
		}
#endif
#ifdef INET6
		if (ptype == SCTP_IPV6_ADDRESS &&
		    plen == sizeof(struct sctp_ipv6addr_param)) {
			/* Get the rest of the address */
			struct sctp_ipv6addr_param ip6_param, *p6;

			phdr = sctp_get_next_param(m, offset,
			    (struct sctp_paramhdr *)&ip6_param, sizeof(ip6_param));
			if (phdr == NULL) {
				return (NULL);
			}
			p6 = (struct sctp_ipv6addr_param *)phdr;
			memcpy(&sin6.sin6_addr, &p6->addr, sizeof(p6->addr));
			/* look it up */
			stcb = sctp_findassociation_ep_addr(inp_p,
			    (struct sockaddr *)&sin6, netp, dst, NULL);
			if (stcb != NULL) {
				return (stcb);
			}
		}
#endif
		offset += SCTP_SIZE32(plen);
		phdr = sctp_get_next_param(m, offset, &param_buf,
		    sizeof(param_buf));
	}
	return (NULL);
}