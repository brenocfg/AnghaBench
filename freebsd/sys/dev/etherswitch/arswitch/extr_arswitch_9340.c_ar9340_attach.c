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
struct TYPE_4__ {int es_vlan_caps; int /*<<< orphan*/  es_nvlangroups; } ;
struct TYPE_3__ {int /*<<< orphan*/  arswitch_atu_learn_default; int /*<<< orphan*/  arswitch_hw_global_setup; int /*<<< orphan*/  arswitch_hw_setup; } ;
struct arswitch_softc {TYPE_2__ info; TYPE_1__ hal; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR8X16_MAX_VLANS ; 
 int ETHERSWITCH_VLAN_DOT1Q ; 
 int ETHERSWITCH_VLAN_DOUBLE_TAG ; 
 int ETHERSWITCH_VLAN_PORT ; 
 int /*<<< orphan*/  ar9340_atu_learn_default ; 
 int /*<<< orphan*/  ar9340_hw_global_setup ; 
 int /*<<< orphan*/  ar9340_hw_setup ; 

void
ar9340_attach(struct arswitch_softc *sc)
{

	sc->hal.arswitch_hw_setup = ar9340_hw_setup;
	sc->hal.arswitch_hw_global_setup = ar9340_hw_global_setup;
	sc->hal.arswitch_atu_learn_default = ar9340_atu_learn_default;
	/*
	 * Note: the ar9340 table fetch code/registers matche
	 * the ar8216/ar8316 for now because we're not supporting
	 * static entry programming that includes any of the extra
	 * bits in the AR9340.
	 */

	/* Set the switch vlan capabilities. */
	sc->info.es_vlan_caps = ETHERSWITCH_VLAN_DOT1Q |
	    ETHERSWITCH_VLAN_PORT | ETHERSWITCH_VLAN_DOUBLE_TAG;
	sc->info.es_nvlangroups = AR8X16_MAX_VLANS;
}