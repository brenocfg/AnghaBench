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
struct walkarg {int w_tmemsize; scalar_t__ w_tmem; int /*<<< orphan*/  w_op; TYPE_1__* w_req; } ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {scalar_t__ sa_family; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct rt_msghdr {int rtm_type; int rtm_msglen; int /*<<< orphan*/  rtm_version; } ;
struct rt_addrinfo {int rti_addrs; struct sockaddr_in6** rti_info; } ;
struct ifma_msghdr {int dummy; } ;
struct ifa_msghdrl32 {int dummy; } ;
struct ifa_msghdrl {int dummy; } ;
struct ifa_msghdr {int dummy; } ;
struct if_msghdrl32 {int dummy; } ;
struct if_msghdrl {int dummy; } ;
struct if_msghdr32 {int dummy; } ;
struct if_msghdr {int dummy; } ;
typedef  struct sockaddr_in6* caddr_t ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int ALIGN (int) ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  NET_RT_IFLISTL ; 
 int RTAX_MAX ; 
#define  RTM_DELADDR 131 
#define  RTM_IFINFO 130 
#define  RTM_NEWADDR 129 
#define  RTM_NEWMADDR 128 
 int /*<<< orphan*/  RTM_VERSION ; 
 int SA_SIZE (struct sockaddr_in6*) ; 
 int SA_SIZE32 (struct sockaddr_in6*) ; 
 int SCTL_MASK32 ; 
 scalar_t__ V_deembed_scopeid ; 
 int /*<<< orphan*/  bcopy (struct sockaddr_in6*,struct sockaddr_in6*,unsigned int) ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in6*,int) ; 
 scalar_t__ sa6_recoverscope (struct sockaddr_in6*) ; 

__attribute__((used)) static int
rtsock_msg_buffer(int type, struct rt_addrinfo *rtinfo, struct walkarg *w, int *plen)
{
	int i;
	int len, buflen = 0, dlen;
	caddr_t cp = NULL;
	struct rt_msghdr *rtm = NULL;
#ifdef INET6
	struct sockaddr_storage ss;
	struct sockaddr_in6 *sin6;
#endif
#ifdef COMPAT_FREEBSD32
	bool compat32 = false;
#endif

	switch (type) {

	case RTM_DELADDR:
	case RTM_NEWADDR:
		if (w != NULL && w->w_op == NET_RT_IFLISTL) {
#ifdef COMPAT_FREEBSD32
			if (w->w_req->flags & SCTL_MASK32) {
				len = sizeof(struct ifa_msghdrl32);
				compat32 = true;
			} else
#endif
				len = sizeof(struct ifa_msghdrl);
		} else
			len = sizeof(struct ifa_msghdr);
		break;

	case RTM_IFINFO:
#ifdef COMPAT_FREEBSD32
		if (w != NULL && w->w_req->flags & SCTL_MASK32) {
			if (w->w_op == NET_RT_IFLISTL)
				len = sizeof(struct if_msghdrl32);
			else
				len = sizeof(struct if_msghdr32);
			compat32 = true;
			break;
		}
#endif
		if (w != NULL && w->w_op == NET_RT_IFLISTL)
			len = sizeof(struct if_msghdrl);
		else
			len = sizeof(struct if_msghdr);
		break;

	case RTM_NEWMADDR:
		len = sizeof(struct ifma_msghdr);
		break;

	default:
		len = sizeof(struct rt_msghdr);
	}

	if (w != NULL) {
		rtm = (struct rt_msghdr *)w->w_tmem;
		buflen = w->w_tmemsize - len;
		cp = (caddr_t)w->w_tmem + len;
	}

	rtinfo->rti_addrs = 0;
	for (i = 0; i < RTAX_MAX; i++) {
		struct sockaddr *sa;

		if ((sa = rtinfo->rti_info[i]) == NULL)
			continue;
		rtinfo->rti_addrs |= (1 << i);
#ifdef COMPAT_FREEBSD32
		if (compat32)
			dlen = SA_SIZE32(sa);
		else
#endif
			dlen = SA_SIZE(sa);
		if (cp != NULL && buflen >= dlen) {
#ifdef INET6
			if (V_deembed_scopeid && sa->sa_family == AF_INET6) {
				sin6 = (struct sockaddr_in6 *)&ss;
				bcopy(sa, sin6, sizeof(*sin6));
				if (sa6_recoverscope(sin6) == 0)
					sa = (struct sockaddr *)sin6;
			}
#endif
			bcopy((caddr_t)sa, cp, (unsigned)dlen);
			cp += dlen;
			buflen -= dlen;
		} else if (cp != NULL) {
			/*
			 * Buffer too small. Count needed size
			 * and return with error.
			 */
			cp = NULL;
		}

		len += dlen;
	}

	if (cp != NULL) {
		dlen = ALIGN(len) - len;
		if (buflen < dlen)
			cp = NULL;
		else {
			bzero(cp, dlen);
			cp += dlen;
			buflen -= dlen;
		}
	}
	len = ALIGN(len);

	if (cp != NULL) {
		/* fill header iff buffer is large enough */
		rtm->rtm_version = RTM_VERSION;
		rtm->rtm_type = type;
		rtm->rtm_msglen = len;
	}

	*plen = len;

	if (w != NULL && cp == NULL)
		return (ENOBUFS);

	return (0);
}