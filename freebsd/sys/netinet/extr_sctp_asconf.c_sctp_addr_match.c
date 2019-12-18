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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int sa_family; } ;
struct sctp_paramhdr {int /*<<< orphan*/  param_length; int /*<<< orphan*/  param_type; } ;
struct sctp_ipv6addr_param {int /*<<< orphan*/  addr; } ;
struct sctp_ipv4addr_param {int /*<<< orphan*/  addr; } ;
struct in_addr {int dummy; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int SCTP_IPV4_ADDRESS ; 
 int SCTP_IPV6_ADDRESS ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
sctp_addr_match(struct sctp_paramhdr *ph, struct sockaddr *sa)
{
#if defined(INET) || defined(INET6)
	uint16_t param_type, param_length;

	param_type = ntohs(ph->param_type);
	param_length = ntohs(ph->param_length);
#endif
	switch (sa->sa_family) {
#ifdef INET6
	case AF_INET6:
		{
			/* XXX scopeid */
			struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)sa;
			struct sctp_ipv6addr_param *v6addr;

			v6addr = (struct sctp_ipv6addr_param *)ph;
			if ((param_type == SCTP_IPV6_ADDRESS) &&
			    (param_length == sizeof(struct sctp_ipv6addr_param)) &&
			    (memcmp(&v6addr->addr, &sin6->sin6_addr,
			    sizeof(struct in6_addr)) == 0)) {
				return (1);
			}
			break;
		}
#endif
#ifdef INET
	case AF_INET:
		{
			struct sockaddr_in *sin = (struct sockaddr_in *)sa;
			struct sctp_ipv4addr_param *v4addr;

			v4addr = (struct sctp_ipv4addr_param *)ph;
			if ((param_type == SCTP_IPV4_ADDRESS) &&
			    (param_length == sizeof(struct sctp_ipv4addr_param)) &&
			    (memcmp(&v4addr->addr, &sin->sin_addr,
			    sizeof(struct in_addr)) == 0)) {
				return (1);
			}
			break;
		}
#endif
	default:
		break;
	}
	return (0);
}