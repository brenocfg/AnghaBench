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
struct sockaddr {scalar_t__ sa_family; } ;
struct route {int dummy; } ;
struct mbuf {int dummy; } ;
struct ifnet {int (* if_transmit ) (struct ifnet*,struct mbuf*) ;} ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int EAFNOSUPPORT ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct ifnet*,struct mbuf*) ; 

__attribute__((used)) static int
uhso_if_output(struct ifnet *ifp, struct mbuf *m0, const struct sockaddr *dst,
    struct route *ro)
{
	int error;

	/* Only IPv4/6 support */
	if (dst->sa_family != AF_INET
#ifdef INET6
	   && dst->sa_family != AF_INET6
#endif
	 ) {
		return (EAFNOSUPPORT);
	}

	error = (ifp->if_transmit)(ifp, m0);
	if (error) {
		if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
		return (ENOBUFS);
	}
	if_inc_counter(ifp, IFCOUNTER_OPACKETS, 1);
	return (0);
}