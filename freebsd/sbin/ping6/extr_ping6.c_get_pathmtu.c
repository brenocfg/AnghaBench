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
struct sockaddr {int dummy; } ;
struct msghdr {int dummy; } ;
struct TYPE_3__ {scalar_t__ sin6_scope_id; int /*<<< orphan*/  sin6_addr; } ;
struct ip6_mtuinfo {scalar_t__ ip6m_mtu; TYPE_1__ ip6m_addr; } ;
struct cmsghdr {scalar_t__ cmsg_len; scalar_t__ cmsg_level; scalar_t__ cmsg_type; } ;
typedef  int /*<<< orphan*/  mtuctl ;
struct TYPE_4__ {scalar_t__ sin6_scope_id; int /*<<< orphan*/  sin6_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMSG_DATA (struct cmsghdr*) ; 
 scalar_t__ CMSG_FIRSTHDR (struct msghdr*) ; 
 scalar_t__ CMSG_LEN (int) ; 
 scalar_t__ CMSG_NXTHDR (struct msghdr*,struct cmsghdr*) ; 
 int F_VERBOSE ; 
 int /*<<< orphan*/  IN6_ARE_ADDR_EQUAL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IPPROTO_IPV6 ; 
 scalar_t__ IPV6_MMTU ; 
 scalar_t__ IPV6_PATHMTU ; 
 TYPE_2__ dst ; 
 int /*<<< orphan*/  memcpy (struct ip6_mtuinfo*,int /*<<< orphan*/ ,int) ; 
 int options ; 
 char* pr_addr (struct sockaddr*,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static int
get_pathmtu(struct msghdr *mhdr)
{
#ifdef IPV6_RECVPATHMTU
	struct cmsghdr *cm;
	struct ip6_mtuinfo mtuctl;

	for (cm = (struct cmsghdr *)CMSG_FIRSTHDR(mhdr); cm;
	     cm = (struct cmsghdr *)CMSG_NXTHDR(mhdr, cm)) {
		if (cm->cmsg_len == 0)
			return(0);

		if (cm->cmsg_level == IPPROTO_IPV6 &&
		    cm->cmsg_type == IPV6_PATHMTU &&
		    cm->cmsg_len == CMSG_LEN(sizeof(struct ip6_mtuinfo))) {
			memcpy(&mtuctl, CMSG_DATA(cm), sizeof(mtuctl));

			/*
			 * If the notified destination is different from
			 * the one we are pinging, just ignore the info.
			 * We check the scope ID only when both notified value
			 * and our own value have non-0 values, because we may
			 * have used the default scope zone ID for sending,
			 * in which case the scope ID value is 0.
			 */
			if (!IN6_ARE_ADDR_EQUAL(&mtuctl.ip6m_addr.sin6_addr,
						&dst.sin6_addr) ||
			    (mtuctl.ip6m_addr.sin6_scope_id &&
			     dst.sin6_scope_id &&
			     mtuctl.ip6m_addr.sin6_scope_id !=
			     dst.sin6_scope_id)) {
				if ((options & F_VERBOSE) != 0) {
					printf("path MTU for %s is notified. "
					       "(ignored)\n",
					   pr_addr((struct sockaddr *)&mtuctl.ip6m_addr,
					   sizeof(mtuctl.ip6m_addr)));
				}
				return(0);
			}

			/*
			 * Ignore an invalid MTU. XXX: can we just believe
			 * the kernel check?
			 */
			if (mtuctl.ip6m_mtu < IPV6_MMTU)
				return(0);

			/* notification for our destination. return the MTU. */
			return((int)mtuctl.ip6m_mtu);
		}
	}
#endif
	return(0);
}