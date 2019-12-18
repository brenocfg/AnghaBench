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
struct sockaddr {int dummy; } ;
struct route {int dummy; } ;
struct mbuf {int dummy; } ;
struct ifnet {int (* if_transmit ) (struct ifnet*,struct mbuf*) ;} ;

/* Variables and functions */
 int stub1 (struct ifnet*,struct mbuf*) ; 

__attribute__((used)) static int
ipsec_output(struct ifnet *ifp, struct mbuf *m, const struct sockaddr *dst,
	struct route *ro)
{

	return (ifp->if_transmit(ifp, m));
}