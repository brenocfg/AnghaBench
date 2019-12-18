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
struct carpreq {int /*<<< orphan*/  carpr_key; int /*<<< orphan*/  carpr_advskew; int /*<<< orphan*/  carpr_advbase; int /*<<< orphan*/  carpr_vhid; int /*<<< orphan*/  carpr_state; } ;
struct carp_softc {int /*<<< orphan*/  sc_key; int /*<<< orphan*/  sc_advskew; int /*<<< orphan*/  sc_advbase; int /*<<< orphan*/  sc_vhid; int /*<<< orphan*/  sc_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARP_LOCK (struct carp_softc*) ; 
 int /*<<< orphan*/  CARP_UNLOCK (struct carp_softc*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
carp_carprcp(struct carpreq *carpr, struct carp_softc *sc, int priv)
{

	CARP_LOCK(sc);
	carpr->carpr_state = sc->sc_state;
	carpr->carpr_vhid = sc->sc_vhid;
	carpr->carpr_advbase = sc->sc_advbase;
	carpr->carpr_advskew = sc->sc_advskew;
	if (priv)
		bcopy(sc->sc_key, carpr->carpr_key, sizeof(carpr->carpr_key));
	else
		bzero(carpr->carpr_key, sizeof(carpr->carpr_key));
	CARP_UNLOCK(sc);
}