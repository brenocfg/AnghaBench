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
struct TYPE_4__ {int /*<<< orphan*/  (* mtkswitch_vlan_init_hw ) (struct mtkswitch_softc*) ;} ;
struct TYPE_3__ {int es_vlan_caps; } ;
struct mtkswitch_softc {int vlan_mode; TYPE_2__ hal; TYPE_1__ info; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  stub1 (struct mtkswitch_softc*) ; 

__attribute__((used)) static int
mtkswitch_set_vlan_mode(struct mtkswitch_softc *sc, uint32_t mode)
{

	/* Check for invalid modes. */
	if ((mode & sc->info.es_vlan_caps) != mode)
		return (EINVAL);

	sc->vlan_mode = mode;

	/* Reset VLANs. */
	sc->hal.mtkswitch_vlan_init_hw(sc);

	return (0);
}