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
struct rm_priotracker {int dummy; } ;
struct TYPE_2__ {int len; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct ifnet {int /*<<< orphan*/  if_xname; int /*<<< orphan*/  if_softc; } ;
typedef  int /*<<< orphan*/  sa_family_t ;
typedef  int /*<<< orphan*/  priv_p ;
typedef  int /*<<< orphan*/ * iffam_p ;
typedef  int /*<<< orphan*/ * hook_p ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int ENETDOWN ; 
 int /*<<< orphan*/  IFCOUNTER_OBYTES ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  NG_FREE_M (struct mbuf*) ; 
 int /*<<< orphan*/  NG_HOOK_REF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_HOOK_UNREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_OUTBOUND_THREAD_REF () ; 
 int /*<<< orphan*/  NG_OUTBOUND_THREAD_UNREF () ; 
 int /*<<< orphan*/  NG_SEND_DATA_ONLY (int,int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  PRIV_RLOCK (int /*<<< orphan*/  const,struct rm_priotracker*) ; 
 int /*<<< orphan*/  PRIV_RUNLOCK (int /*<<< orphan*/  const,struct rm_priotracker*) ; 
 int /*<<< orphan*/ ** get_hook_from_iffam (int /*<<< orphan*/  const,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/ * get_iffam_from_af (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

__attribute__((used)) static int
ng_iface_send(struct ifnet *ifp, struct mbuf *m, sa_family_t sa)
{
	struct rm_priotracker priv_tracker;
	const priv_p priv = (priv_p) ifp->if_softc;
	const iffam_p iffam = get_iffam_from_af(sa);
	hook_p hook;
	int error;
	int len;

	/* Check address family to determine hook (if known) */
	if (iffam == NULL) {
		m_freem(m);
		log(LOG_WARNING, "%s: can't handle af%d\n", ifp->if_xname, sa);
		return (EAFNOSUPPORT);
	}

	/* Copy length before the mbuf gets invalidated. */
	len = m->m_pkthdr.len;

	PRIV_RLOCK(priv, &priv_tracker);
	hook = *get_hook_from_iffam(priv, iffam);
	if (hook == NULL) {
		NG_FREE_M(m);
		PRIV_RUNLOCK(priv, &priv_tracker);
		return ENETDOWN;
	}
	NG_HOOK_REF(hook);
	PRIV_RUNLOCK(priv, &priv_tracker);

	NG_OUTBOUND_THREAD_REF();
	NG_SEND_DATA_ONLY(error, hook, m);
	NG_OUTBOUND_THREAD_UNREF();
	NG_HOOK_UNREF(hook);

	/* Update stats. */
	if (error == 0) {
		if_inc_counter(ifp, IFCOUNTER_OBYTES, len);
		if_inc_counter(ifp, IFCOUNTER_OPACKETS, 1);
	}

	return (error);
}