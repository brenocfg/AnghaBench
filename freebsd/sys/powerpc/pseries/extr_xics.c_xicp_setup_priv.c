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
typedef  int /*<<< orphan*/  u_int ;
struct xicp_softc {scalar_t__ nintvecs; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/ * intvecs; } ;
typedef  void xicp_intvec ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ nitems (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline struct xicp_intvec *
xicp_setup_priv(struct xicp_softc *sc, u_int irq, void **priv)
{
	if (*priv == NULL) {
		KASSERT(sc->nintvecs + 1 < nitems(sc->intvecs),
			("Too many XICP interrupts"));
		mtx_lock(&sc->sc_mtx);
		*priv = &sc->intvecs[sc->nintvecs++];
		mtx_unlock(&sc->sc_mtx);
	}

	return (*priv);
}