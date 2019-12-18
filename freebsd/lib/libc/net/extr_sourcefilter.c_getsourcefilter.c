#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
struct __msfilterreq {scalar_t__ msfr_fmode; int msfr_nsrcs; struct sockaddr_storage* msfr_srcs; int /*<<< orphan*/  msfr_group; scalar_t__ msfr_ifindex; } ;
struct TYPE_10__ {int ss_family; int /*<<< orphan*/  ss_len; } ;
struct TYPE_8__ {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_7__ {TYPE_1__ sin_addr; } ;
struct TYPE_9__ {TYPE_5__ ss; TYPE_3__ sin6; TYPE_2__ sin; } ;
typedef  TYPE_4__ sockunion_t ;
typedef  int socklen_t ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  EAFNOSUPPORT ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  IN6_IS_ADDR_MULTICAST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IN_MULTICAST (int /*<<< orphan*/ ) ; 
 int IPPROTO_IP ; 
 int IPPROTO_IPV6 ; 
 int IPV6_MSFILTER ; 
 int IP_MSFILTER ; 
 int _getsockopt (int,int,int,struct __msfilterreq*,int*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct __msfilterreq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

int
getsourcefilter(int s, uint32_t interface, struct sockaddr *group,
    socklen_t grouplen, uint32_t *fmode, uint32_t *numsrc,
    struct sockaddr_storage *slist)
{
	struct __msfilterreq	 msfr;
	sockunion_t		*psu;
	socklen_t		 optlen;
	int			 err, level, nsrcs, optname;

	if (interface == 0 || group == NULL || numsrc == NULL ||
	    fmode == NULL) {
		errno = EINVAL;
		return (-1);
	}

	nsrcs = *numsrc;
	*numsrc = 0;
	*fmode = 0;

	psu = (sockunion_t *)group;
	switch (psu->ss.ss_family) {
#ifdef INET
	case AF_INET:
		if ((grouplen != sizeof(struct sockaddr_in) ||
		    !IN_MULTICAST(ntohl(psu->sin.sin_addr.s_addr)))) {
			errno = EINVAL;
			return (-1);
		}
		level = IPPROTO_IP;
		optname = IP_MSFILTER;
		break;
#endif
#ifdef INET6
	case AF_INET6:
		if (grouplen != sizeof(struct sockaddr_in6) ||
		    !IN6_IS_ADDR_MULTICAST(&psu->sin6.sin6_addr)) {
			errno = EINVAL;
			return (-1);
		}
		level = IPPROTO_IPV6;
		optname = IPV6_MSFILTER;
		break;
#endif
	default:
		errno = EAFNOSUPPORT;
		return (-1);
		break;
	}

	optlen = sizeof(struct __msfilterreq);
	memset(&msfr, 0, optlen);
	msfr.msfr_ifindex = interface;
	msfr.msfr_fmode = 0;
	msfr.msfr_nsrcs = nsrcs;
	memcpy(&msfr.msfr_group, &psu->ss, psu->ss.ss_len);

	/*
	 * msfr_srcs is a pointer to a vector of sockaddr_storage. It
	 * may be NULL. The kernel will always return the total number
	 * of filter entries for the group in msfr.msfr_nsrcs.
	 */
	msfr.msfr_srcs = slist;
	err = _getsockopt(s, level, optname, &msfr, &optlen);
	if (err == 0) {
		*numsrc = msfr.msfr_nsrcs;
		*fmode = msfr.msfr_fmode;
	}

	return (err);
}