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
struct ifvlan {int dummy; } ;
struct ifnet {int (* if_output ) (struct ifnet*,struct mbuf*,struct sockaddr const*,struct route*) ;struct ifvlan* if_softc; } ;

/* Variables and functions */
 int ENETDOWN ; 
 int /*<<< orphan*/  NET_EPOCH_ASSERT () ; 
 struct ifnet* PARENT (struct ifvlan*) ; 
 int /*<<< orphan*/ * TRUNK (struct ifvlan*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int stub1 (struct ifnet*,struct mbuf*,struct sockaddr const*,struct route*) ; 

__attribute__((used)) static int
vlan_output(struct ifnet *ifp, struct mbuf *m, const struct sockaddr *dst,
    struct route *ro)
{
	struct ifvlan *ifv;
	struct ifnet *p;

	NET_EPOCH_ASSERT();

	ifv = ifp->if_softc;
	if (TRUNK(ifv) == NULL) {
		m_freem(m);
		return (ENETDOWN);
	}
	p = PARENT(ifv);
	return p->if_output(ifp, m, dst, ro);
}