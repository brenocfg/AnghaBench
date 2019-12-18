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
struct sockaddr {int sa_family; } ;
struct route {int dummy; } ;
struct mbuf {int dummy; } ;
struct lagg_port {int (* lp_output ) (struct ifnet*,struct mbuf*,struct sockaddr const*,struct route*) ;} ;
struct ifnet {struct lagg_port* if_lagg; } ;

/* Variables and functions */
#define  AF_UNSPEC 129 
 int ENETDOWN ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
#define  pseudo_AF_HDRCMPLT 128 
 int stub1 (struct ifnet*,struct mbuf*,struct sockaddr const*,struct route*) ; 

__attribute__((used)) static int
lagg_port_output(struct ifnet *ifp, struct mbuf *m,
	const struct sockaddr *dst, struct route *ro)
{
	struct lagg_port *lp = ifp->if_lagg;

	switch (dst->sa_family) {
		case pseudo_AF_HDRCMPLT:
		case AF_UNSPEC:
			return ((*lp->lp_output)(ifp, m, dst, ro));
	}

	/* drop any other frames */
	m_freem(m);
	return (ENETDOWN);
}