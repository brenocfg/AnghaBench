#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_7__ {int /*<<< orphan*/  ifp; int /*<<< orphan*/ * vlan_detach; int /*<<< orphan*/ * vlan_attach; int /*<<< orphan*/  timer; int /*<<< orphan*/  dev_lock; struct TYPE_7__* next; } ;
typedef  TYPE_1__* POCE_SOFTC ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oce_hw_shutdown (TYPE_1__*) ; 
 int /*<<< orphan*/  oce_if_deactivate (TYPE_1__*) ; 
 TYPE_1__* softc_head ; 
 TYPE_1__* softc_tail ; 
 int /*<<< orphan*/  vlan_config ; 
 int /*<<< orphan*/  vlan_unconfig ; 

__attribute__((used)) static int
oce_detach(device_t dev)
{
	POCE_SOFTC sc = device_get_softc(dev);
	POCE_SOFTC poce_sc_tmp, *ppoce_sc_tmp1, poce_sc_tmp2 = NULL;

        poce_sc_tmp = softc_head;
        ppoce_sc_tmp1 = &softc_head;
        while (poce_sc_tmp != NULL) {
          if (poce_sc_tmp == sc) {
            *ppoce_sc_tmp1 = sc->next;
            if (sc->next == NULL) {
              softc_tail = poce_sc_tmp2;
            }
            break;
          }
          poce_sc_tmp2 = poce_sc_tmp;
          ppoce_sc_tmp1 = &poce_sc_tmp->next;
          poce_sc_tmp = poce_sc_tmp->next;
        }

	LOCK(&sc->dev_lock);
	oce_if_deactivate(sc);
	UNLOCK(&sc->dev_lock);

	callout_drain(&sc->timer);
	
	if (sc->vlan_attach != NULL)
		EVENTHANDLER_DEREGISTER(vlan_config, sc->vlan_attach);
	if (sc->vlan_detach != NULL)
		EVENTHANDLER_DEREGISTER(vlan_unconfig, sc->vlan_detach);

	ether_ifdetach(sc->ifp);

	if_free(sc->ifp);

	oce_hw_shutdown(sc);

	bus_generic_detach(dev);

	return 0;
}