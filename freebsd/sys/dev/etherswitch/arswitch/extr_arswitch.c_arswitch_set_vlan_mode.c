#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* arswitch_vlan_init_hw ) (struct arswitch_softc*) ;} ;
struct TYPE_3__ {int es_vlan_caps; } ;
struct arswitch_softc {int vlan_mode; TYPE_2__ hal; TYPE_1__ info; } ;

/* Variables and functions */
 int EINVAL ; 
#define  ETHERSWITCH_VLAN_DOT1Q 129 
#define  ETHERSWITCH_VLAN_PORT 128 
 int /*<<< orphan*/  stub1 (struct arswitch_softc*) ; 

__attribute__((used)) static int
arswitch_set_vlan_mode(struct arswitch_softc *sc, uint32_t mode)
{

	/* Check for invalid modes. */
	if ((mode & sc->info.es_vlan_caps) != mode)
		return (EINVAL);

	switch (mode) {
	case ETHERSWITCH_VLAN_DOT1Q:
		sc->vlan_mode = ETHERSWITCH_VLAN_DOT1Q;
		break;
	case ETHERSWITCH_VLAN_PORT:
		sc->vlan_mode = ETHERSWITCH_VLAN_PORT;
		break;
	default:
		sc->vlan_mode = 0;
	}

	/* Reset VLANs. */
	sc->hal.arswitch_vlan_init_hw(sc);

	return (0);
}