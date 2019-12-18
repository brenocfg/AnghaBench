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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
struct sockaddr {int dummy; } ;
struct mbuf {int m_flags; } ;
struct llentry {int r_flags; int /*<<< orphan*/  r_hdrlen; int /*<<< orphan*/  r_linkdata; } ;
struct ifnet {int /*<<< orphan*/  if_addrlen; int /*<<< orphan*/  if_broadcastaddr; } ;
struct TYPE_2__ {int /*<<< orphan*/  sin_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_MAP_IP_MULTICAST (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LLE_ADDREF (struct llentry*) ; 
 int /*<<< orphan*/  LLE_CREATE ; 
 int /*<<< orphan*/  LLE_EXCLUSIVE ; 
 int /*<<< orphan*/  LLE_UNLOCKED ; 
 int LLE_VALID ; 
 int /*<<< orphan*/  LLE_WUNLOCK (struct llentry*) ; 
 int /*<<< orphan*/  LLTABLE (struct ifnet*) ; 
 int M_BCAST ; 
 int M_MCAST ; 
 int /*<<< orphan*/  NET_EPOCH_ASSERT () ; 
 int RLLE_IFADDR ; 
 int RLLE_VALID ; 
 TYPE_1__* SIN (struct sockaddr const*) ; 
 int arpresolve_full (struct ifnet*,int,int /*<<< orphan*/ ,struct mbuf*,struct sockaddr const*,int /*<<< orphan*/ *,int*,struct llentry**) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct llentry* lla_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr const*) ; 
 int /*<<< orphan*/  llentry_mark_used (struct llentry*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
arpresolve(struct ifnet *ifp, int is_gw, struct mbuf *m,
	const struct sockaddr *dst, u_char *desten, uint32_t *pflags,
	struct llentry **plle)
{
	struct llentry *la = NULL;

	NET_EPOCH_ASSERT();

	if (pflags != NULL)
		*pflags = 0;
	if (plle != NULL)
		*plle = NULL;

	if (m != NULL) {
		if (m->m_flags & M_BCAST) {
			/* broadcast */
			(void)memcpy(desten,
			    ifp->if_broadcastaddr, ifp->if_addrlen);
			return (0);
		}
		if (m->m_flags & M_MCAST) {
			/* multicast */
			ETHER_MAP_IP_MULTICAST(&SIN(dst)->sin_addr, desten);
			return (0);
		}
	}

	la = lla_lookup(LLTABLE(ifp), plle ? LLE_EXCLUSIVE : LLE_UNLOCKED, dst);
	if (la != NULL && (la->r_flags & RLLE_VALID) != 0) {
		/* Entry found, let's copy lle info */
		bcopy(la->r_linkdata, desten, la->r_hdrlen);
		if (pflags != NULL)
			*pflags = LLE_VALID | (la->r_flags & RLLE_IFADDR);
		/* Notify the LLE handling code that the entry was used. */
		llentry_mark_used(la);
		if (plle) {
			LLE_ADDREF(la);
			*plle = la;
			LLE_WUNLOCK(la);
		}
		return (0);
	}
	if (plle && la)
		LLE_WUNLOCK(la);

	return (arpresolve_full(ifp, is_gw, la == NULL ? LLE_CREATE : 0, m, dst,
	    desten, pflags, plle));
}