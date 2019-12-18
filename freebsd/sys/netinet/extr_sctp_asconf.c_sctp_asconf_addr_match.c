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
typedef  int uint32_t ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int sa_family; } ;
struct TYPE_4__ {int /*<<< orphan*/  param_type; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr; TYPE_1__ ph; } ;
struct TYPE_6__ {TYPE_2__ addrp; } ;
struct sctp_asconf_addr {TYPE_3__ ap; } ;
struct in_addr {int dummy; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  SCTP_IPV4_ADDRESS ; 
 int /*<<< orphan*/  SCTP_IPV6_ADDRESS ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static uint32_t
sctp_asconf_addr_match(struct sctp_asconf_addr *aa, struct sockaddr *sa)
{
	switch (sa->sa_family) {
#ifdef INET6
	case AF_INET6:
		{
			/* XXX scopeid */
			struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)sa;

			if ((aa->ap.addrp.ph.param_type == SCTP_IPV6_ADDRESS) &&
			    (memcmp(&aa->ap.addrp.addr, &sin6->sin6_addr,
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

			if ((aa->ap.addrp.ph.param_type == SCTP_IPV4_ADDRESS) &&
			    (memcmp(&aa->ap.addrp.addr, &sin->sin_addr,
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