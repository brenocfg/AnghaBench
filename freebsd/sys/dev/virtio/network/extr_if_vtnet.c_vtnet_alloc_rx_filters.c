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
typedef  int /*<<< orphan*/  uint32_t ;
struct vtnet_softc {int vtnet_flags; int /*<<< orphan*/ * vtnet_vlan_filter; int /*<<< orphan*/ * vtnet_mac_filter; } ;
struct vtnet_mac_filter {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int VTNET_FLAG_CTRL_RX ; 
 int VTNET_FLAG_VLAN_FILTER ; 
 int VTNET_VLAN_FILTER_NWORDS ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
vtnet_alloc_rx_filters(struct vtnet_softc *sc)
{

	if (sc->vtnet_flags & VTNET_FLAG_CTRL_RX) {
		sc->vtnet_mac_filter = malloc(sizeof(struct vtnet_mac_filter),
		    M_DEVBUF, M_NOWAIT | M_ZERO);
		if (sc->vtnet_mac_filter == NULL)
			return (ENOMEM);
	}

	if (sc->vtnet_flags & VTNET_FLAG_VLAN_FILTER) {
		sc->vtnet_vlan_filter = malloc(sizeof(uint32_t) *
		    VTNET_VLAN_FILTER_NWORDS, M_DEVBUF, M_NOWAIT | M_ZERO);
		if (sc->vtnet_vlan_filter == NULL)
			return (ENOMEM);
	}

	return (0);
}