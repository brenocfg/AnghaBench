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
typedef  scalar_t__ uint32_t ;
struct sockaddr {scalar_t__ sa_family; int /*<<< orphan*/  sa_data; } ;
struct route {int dummy; } ;
struct mbuf {scalar_t__ m_data; } ;
struct ifnet {int if_flags; int if_drv_flags; int (* if_transmit ) (struct ifnet*,struct mbuf*) ;int /*<<< orphan*/  if_snd; } ;
typedef  scalar_t__ sa_family_t ;
typedef  int /*<<< orphan*/  af ;

/* Variables and functions */
 scalar_t__ AF_UNSPEC ; 
 scalar_t__ ALTQ_IS_ENABLED (int /*<<< orphan*/ *) ; 
 int ENETDOWN ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  IFCOUNTER_OQDROPS ; 
 int IFF_DRV_RUNNING ; 
 int IFF_UP ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_PREPEND (struct mbuf*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NGM_IFACE_COOKIE ; 
 int /*<<< orphan*/  V_ng_iface_max_nest ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int if_tunnel_check_nesting (struct ifnet*,struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  ng_iface_bpftap (struct ifnet*,struct mbuf*,scalar_t__) ; 
 int ng_iface_send (struct ifnet*,struct mbuf*,scalar_t__) ; 
 int stub1 (struct ifnet*,struct mbuf*) ; 

__attribute__((used)) static int
ng_iface_output(struct ifnet *ifp, struct mbuf *m,
	const struct sockaddr *dst, struct route *ro)
{
	uint32_t af;
	int error;

	/* Check interface flags */
	if (!((ifp->if_flags & IFF_UP) &&
	    (ifp->if_drv_flags & IFF_DRV_RUNNING))) {
		m_freem(m);
		return (ENETDOWN);
	}

	/* Protect from deadly infinite recursion. */
	error = if_tunnel_check_nesting(ifp, m, NGM_IFACE_COOKIE,
	    V_ng_iface_max_nest);
	if (error) {
		m_freem(m);
		return (error);
	}

	/* BPF writes need to be handled specially. */
	if (dst->sa_family == AF_UNSPEC)
		bcopy(dst->sa_data, &af, sizeof(af));
	else
		af = dst->sa_family;

	/* Berkeley packet filter */
	ng_iface_bpftap(ifp, m, af);

	if (ALTQ_IS_ENABLED(&ifp->if_snd)) {
		M_PREPEND(m, sizeof(sa_family_t), M_NOWAIT);
		if (m == NULL) {
			if_inc_counter(ifp, IFCOUNTER_OQDROPS, 1);
			return (ENOBUFS);
		}
		*(sa_family_t *)m->m_data = af;
		error = (ifp->if_transmit)(ifp, m);
	} else
		error = ng_iface_send(ifp, m, af);

	return (error);
}