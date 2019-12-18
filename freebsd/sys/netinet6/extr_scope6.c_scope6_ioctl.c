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
typedef  int u_long ;
struct scope6_id {int dummy; } ;
struct TYPE_2__ {scalar_t__ ifru_scope_id; } ;
struct in6_ifreq {TYPE_1__ ifr_ifru; } ;
struct ifnet {int /*<<< orphan*/ ** if_afdata; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 size_t AF_INET6 ; 
 int EOPNOTSUPP ; 
 int EPFNOSUPPORT ; 
#define  SIOCGSCOPE6 130 
#define  SIOCGSCOPE6DEF 129 
#define  SIOCSSCOPE6 128 
 int scope6_get (struct ifnet*,struct scope6_id*) ; 
 int scope6_get_default (struct scope6_id*) ; 
 int scope6_set (struct ifnet*,struct scope6_id*) ; 

int
scope6_ioctl(u_long cmd, caddr_t data, struct ifnet *ifp)
{
	struct in6_ifreq *ifr;

	if (ifp->if_afdata[AF_INET6] == NULL)
		return (EPFNOSUPPORT);

	ifr = (struct in6_ifreq *)data;
	switch (cmd) {
	case SIOCSSCOPE6:
		return (scope6_set(ifp,
		    (struct scope6_id *)ifr->ifr_ifru.ifru_scope_id));
	case SIOCGSCOPE6:
		return (scope6_get(ifp,
		    (struct scope6_id *)ifr->ifr_ifru.ifru_scope_id));
	case SIOCGSCOPE6DEF:
		return (scope6_get_default(
		    (struct scope6_id *)ifr->ifr_ifru.ifru_scope_id));
	default:
		return (EOPNOTSUPP);
	}
}