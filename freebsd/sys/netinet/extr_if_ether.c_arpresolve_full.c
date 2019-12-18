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
struct mbuf {struct mbuf* m_nextpkt; } ;
struct llentry {int la_flags; scalar_t__ la_expire; char* ll_addr; char* r_linkdata; int r_hdrlen; scalar_t__ la_asked; scalar_t__ la_numheld; int /*<<< orphan*/  lle_timer; struct mbuf* la_hold; } ;
struct ifnet {int if_flags; int if_addrlen; } ;
struct TYPE_2__ {int /*<<< orphan*/  sin_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPSTAT_INC (int /*<<< orphan*/ ) ; 
 int EHOSTDOWN ; 
 int EHOSTUNREACH ; 
 int EINVAL ; 
 int EWOULDBLOCK ; 
 int IFF_NOARP ; 
 int IFF_STATICARP ; 
 int /*<<< orphan*/  IF_AFDATA_WLOCK (struct ifnet*) ; 
 int /*<<< orphan*/  IF_AFDATA_WUNLOCK (struct ifnet*) ; 
 int INET_ADDRSTRLEN ; 
 int /*<<< orphan*/  LLE_ADDREF (struct llentry*) ; 
 int LLE_ADDRONLY ; 
 int LLE_CREATE ; 
 int /*<<< orphan*/  LLE_EXCLUSIVE ; 
 int LLE_IFADDR ; 
 int /*<<< orphan*/  LLE_REMREF (struct llentry*) ; 
 int LLE_STATIC ; 
 int LLE_VALID ; 
 int /*<<< orphan*/  LLE_WLOCK (struct llentry*) ; 
 int /*<<< orphan*/  LLE_WUNLOCK (struct llentry*) ; 
 int /*<<< orphan*/  LLTABLE (struct ifnet*) ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  NET_EPOCH_ASSERT () ; 
 TYPE_1__* SIN (struct sockaddr const*) ; 
 scalar_t__ V_arp_maxhold ; 
 scalar_t__ V_arp_maxtries ; 
 int V_arpt_down ; 
 int arprequest_internal (struct ifnet*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arptimer ; 
 int /*<<< orphan*/  bcopy (char*,int /*<<< orphan*/ *,int) ; 
 int callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct llentry*) ; 
 int /*<<< orphan*/  dropped ; 
 int hz ; 
 int /*<<< orphan*/  if_name (struct ifnet*) ; 
 int /*<<< orphan*/  inet_ntoa_r (int /*<<< orphan*/ ,char*) ; 
 struct llentry* lla_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr const*) ; 
 int /*<<< orphan*/  llentry_mark_used (struct llentry*) ; 
 struct llentry* lltable_alloc_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr const*) ; 
 int /*<<< orphan*/  lltable_free_entry (int /*<<< orphan*/ ,struct llentry*) ; 
 int /*<<< orphan*/  lltable_link_entry (int /*<<< orphan*/ ,struct llentry*) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 scalar_t__ time_uptime ; 

__attribute__((used)) static int
arpresolve_full(struct ifnet *ifp, int is_gw, int flags, struct mbuf *m,
	const struct sockaddr *dst, u_char *desten, uint32_t *pflags,
	struct llentry **plle)
{
	struct llentry *la = NULL, *la_tmp;
	struct mbuf *curr = NULL;
	struct mbuf *next = NULL;
	int error, renew;
	char *lladdr;
	int ll_len;

	NET_EPOCH_ASSERT();

	if (pflags != NULL)
		*pflags = 0;
	if (plle != NULL)
		*plle = NULL;

	if ((flags & LLE_CREATE) == 0)
		la = lla_lookup(LLTABLE(ifp), LLE_EXCLUSIVE, dst);
	if (la == NULL && (ifp->if_flags & (IFF_NOARP | IFF_STATICARP)) == 0) {
		la = lltable_alloc_entry(LLTABLE(ifp), 0, dst);
		if (la == NULL) {
			char addrbuf[INET_ADDRSTRLEN];

			log(LOG_DEBUG,
			    "arpresolve: can't allocate llinfo for %s on %s\n",
			    inet_ntoa_r(SIN(dst)->sin_addr, addrbuf),
			    if_name(ifp));
			m_freem(m);
			return (EINVAL);
		}

		IF_AFDATA_WLOCK(ifp);
		LLE_WLOCK(la);
		la_tmp = lla_lookup(LLTABLE(ifp), LLE_EXCLUSIVE, dst);
		/* Prefer ANY existing lle over newly-created one */
		if (la_tmp == NULL)
			lltable_link_entry(LLTABLE(ifp), la);
		IF_AFDATA_WUNLOCK(ifp);
		if (la_tmp != NULL) {
			lltable_free_entry(LLTABLE(ifp), la);
			la = la_tmp;
		}
	}
	if (la == NULL) {
		m_freem(m);
		return (EINVAL);
	}

	if ((la->la_flags & LLE_VALID) &&
	    ((la->la_flags & LLE_STATIC) || la->la_expire > time_uptime)) {
		if (flags & LLE_ADDRONLY) {
			lladdr = la->ll_addr;
			ll_len = ifp->if_addrlen;
		} else {
			lladdr = la->r_linkdata;
			ll_len = la->r_hdrlen;
		}
		bcopy(lladdr, desten, ll_len);

		/* Notify LLE code that the entry was used by datapath */
		llentry_mark_used(la);
		if (pflags != NULL)
			*pflags = la->la_flags & (LLE_VALID|LLE_IFADDR);
		if (plle) {
			LLE_ADDREF(la);
			*plle = la;
		}
		LLE_WUNLOCK(la);
		return (0);
	}

	renew = (la->la_asked == 0 || la->la_expire != time_uptime);
	/*
	 * There is an arptab entry, but no ethernet address
	 * response yet.  Add the mbuf to the list, dropping
	 * the oldest packet if we have exceeded the system
	 * setting.
	 */
	if (m != NULL) {
		if (la->la_numheld >= V_arp_maxhold) {
			if (la->la_hold != NULL) {
				next = la->la_hold->m_nextpkt;
				m_freem(la->la_hold);
				la->la_hold = next;
				la->la_numheld--;
				ARPSTAT_INC(dropped);
			}
		}
		if (la->la_hold != NULL) {
			curr = la->la_hold;
			while (curr->m_nextpkt != NULL)
				curr = curr->m_nextpkt;
			curr->m_nextpkt = m;
		} else
			la->la_hold = m;
		la->la_numheld++;
	}
	/*
	 * Return EWOULDBLOCK if we have tried less than arp_maxtries. It
	 * will be masked by ether_output(). Return EHOSTDOWN/EHOSTUNREACH
	 * if we have already sent arp_maxtries ARP requests. Retransmit the
	 * ARP request, but not faster than one request per second.
	 */
	if (la->la_asked < V_arp_maxtries)
		error = EWOULDBLOCK;	/* First request. */
	else
		error = is_gw != 0 ? EHOSTUNREACH : EHOSTDOWN;

	if (renew) {
		int canceled, e;

		LLE_ADDREF(la);
		la->la_expire = time_uptime;
		canceled = callout_reset(&la->lle_timer, hz * V_arpt_down,
		    arptimer, la);
		if (canceled)
			LLE_REMREF(la);
		la->la_asked++;
		LLE_WUNLOCK(la);
		e = arprequest_internal(ifp, NULL, &SIN(dst)->sin_addr, NULL);
		/*
		 * Only overwrite 'error' in case of error; in case of success
		 * the proper return value was already set above.
		 */
		if (e != 0)
			return (e);
		return (error);
	}

	LLE_WUNLOCK(la);
	return (error);
}