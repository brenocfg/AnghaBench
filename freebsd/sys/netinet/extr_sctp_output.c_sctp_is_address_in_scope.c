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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_3__ sin_addr; } ;
struct sctp_scoping {scalar_t__ loopback_scope; int /*<<< orphan*/  site_scope; int /*<<< orphan*/  ipv6_addr_legal; int /*<<< orphan*/  ipv4_local_scope; int /*<<< orphan*/  ipv4_addr_legal; } ;
struct TYPE_4__ {int sa_family; } ;
struct TYPE_5__ {struct sockaddr_in6 sin6; struct sockaddr_in sin; TYPE_1__ sa; } ;
struct sctp_ifa {int localifa_flags; TYPE_2__ address; scalar_t__ ifn_p; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  IN4_ISPRIVATE_ADDRESS (TYPE_3__*) ; 
 int /*<<< orphan*/  IN6_IS_ADDR_LINKLOCAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IN6_IS_ADDR_SITELOCAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IN6_IS_ADDR_UNSPECIFIED (int /*<<< orphan*/ *) ; 
 int SCTP_ADDR_IFA_UNUSEABLE ; 
 scalar_t__ SCTP_IFN_IS_IFT_LOOP (scalar_t__) ; 
 int /*<<< orphan*/  sctp_gather_internal_ifa_flags (struct sctp_ifa*) ; 

int
sctp_is_address_in_scope(struct sctp_ifa *ifa,
    struct sctp_scoping *scope,
    int do_update)
{
	if ((scope->loopback_scope == 0) &&
	    (ifa->ifn_p) && SCTP_IFN_IS_IFT_LOOP(ifa->ifn_p)) {
		/*
		 * skip loopback if not in scope *
		 */
		return (0);
	}
	switch (ifa->address.sa.sa_family) {
#ifdef INET
	case AF_INET:
		if (scope->ipv4_addr_legal) {
			struct sockaddr_in *sin;

			sin = &ifa->address.sin;
			if (sin->sin_addr.s_addr == 0) {
				/* not in scope , unspecified */
				return (0);
			}
			if ((scope->ipv4_local_scope == 0) &&
			    (IN4_ISPRIVATE_ADDRESS(&sin->sin_addr))) {
				/* private address not in scope */
				return (0);
			}
		} else {
			return (0);
		}
		break;
#endif
#ifdef INET6
	case AF_INET6:
		if (scope->ipv6_addr_legal) {
			struct sockaddr_in6 *sin6;

			/*
			 * Must update the flags,  bummer, which means any
			 * IFA locks must now be applied HERE <->
			 */
			if (do_update) {
				sctp_gather_internal_ifa_flags(ifa);
			}
			if (ifa->localifa_flags & SCTP_ADDR_IFA_UNUSEABLE) {
				return (0);
			}
			/* ok to use deprecated addresses? */
			sin6 = &ifa->address.sin6;
			if (IN6_IS_ADDR_UNSPECIFIED(&sin6->sin6_addr)) {
				/* skip unspecifed addresses */
				return (0);
			}
			if (	/* (local_scope == 0) && */
			    (IN6_IS_ADDR_LINKLOCAL(&sin6->sin6_addr))) {
				return (0);
			}
			if ((scope->site_scope == 0) &&
			    (IN6_IS_ADDR_SITELOCAL(&sin6->sin6_addr))) {
				return (0);
			}
		} else {
			return (0);
		}
		break;
#endif
	default:
		return (0);
	}
	return (1);
}