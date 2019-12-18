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
typedef  scalar_t__ uint32_t ;
struct sockaddr {scalar_t__ sa_family; int /*<<< orphan*/  sa_data; } ;
struct route {int dummy; } ;
struct TYPE_2__ {scalar_t__ csum_data; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct ifnet {int (* if_transmit ) (struct ifnet*,struct mbuf*) ;} ;
typedef  int /*<<< orphan*/  af ;

/* Variables and functions */
 scalar_t__ AF_UNSPEC ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int stub1 (struct ifnet*,struct mbuf*) ; 

int
gif_output(struct ifnet *ifp, struct mbuf *m, const struct sockaddr *dst,
	struct route *ro)
{
	uint32_t af;

	if (dst->sa_family == AF_UNSPEC)
		bcopy(dst->sa_data, &af, sizeof(af));
	else
		af = dst->sa_family;
	/*
	 * Now save the af in the inbound pkt csum data, this is a cheat since
	 * we are using the inbound csum_data field to carry the af over to
	 * the gif_transmit() routine, avoiding using yet another mtag.
	 */
	m->m_pkthdr.csum_data = af;
	return (ifp->if_transmit(ifp, m));
}