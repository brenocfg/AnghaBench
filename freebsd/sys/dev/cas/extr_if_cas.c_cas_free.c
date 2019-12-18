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
typedef  size_t u_int ;
struct TYPE_2__ {scalar_t__ ext_arg2; struct cas_softc* ext_arg1; } ;
struct mbuf {TYPE_1__ m_ext; } ;
struct cas_softc {struct cas_rxdsoft* sc_rxdsoft; } ;
struct cas_rxdsoft {int /*<<< orphan*/  rxds_refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAS_LOCK (struct cas_softc*) ; 
 size_t CAS_LOCK_OWNED (struct cas_softc*) ; 
 int /*<<< orphan*/  CAS_UNLOCK (struct cas_softc*) ; 
 int /*<<< orphan*/  cas_add_rxdesc (struct cas_softc*,size_t) ; 
 scalar_t__ refcount_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cas_free(struct mbuf *m)
{
	struct cas_rxdsoft *rxds;
	struct cas_softc *sc;
	u_int idx, locked;

	sc = m->m_ext.ext_arg1;
	idx = (uintptr_t)m->m_ext.ext_arg2;
	rxds = &sc->sc_rxdsoft[idx];
	if (refcount_release(&rxds->rxds_refcount) == 0)
		return;

	/*
	 * NB: this function can be called via m_freem(9) within
	 * this driver!
	 */
	if ((locked = CAS_LOCK_OWNED(sc)) == 0)
		CAS_LOCK(sc);
	cas_add_rxdesc(sc, idx);
	if (locked == 0)
		CAS_UNLOCK(sc);
}