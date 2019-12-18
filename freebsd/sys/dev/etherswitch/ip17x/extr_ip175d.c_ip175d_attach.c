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
struct TYPE_3__ {int /*<<< orphan*/  es_vlan_caps; } ;
struct TYPE_4__ {int /*<<< orphan*/  ip17x_set_vlan_mode; int /*<<< orphan*/  ip17x_get_vlan_mode; int /*<<< orphan*/  ip17x_hw_setup; int /*<<< orphan*/  ip17x_reset; } ;
struct ip17x_softc {int /*<<< orphan*/  sc_dev; TYPE_1__ info; int /*<<< orphan*/  numports; int /*<<< orphan*/  cpuport; TYPE_2__ hal; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHERSWITCH_VLAN_DOT1Q ; 
 int /*<<< orphan*/  IP175X_CPU_PORT ; 
 int /*<<< orphan*/  IP175X_NUM_PORTS ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ip175d_get_vlan_mode ; 
 int /*<<< orphan*/  ip175d_hw_setup ; 
 int /*<<< orphan*/  ip175d_reset ; 
 int /*<<< orphan*/  ip175d_set_vlan_mode ; 

void
ip175d_attach(struct ip17x_softc *sc)
{

	sc->hal.ip17x_reset = ip175d_reset;
	sc->hal.ip17x_hw_setup = ip175d_hw_setup;
	sc->hal.ip17x_get_vlan_mode = ip175d_get_vlan_mode;
	sc->hal.ip17x_set_vlan_mode = ip175d_set_vlan_mode;

	/* Defaults for IP175C. */
	sc->cpuport = IP175X_CPU_PORT;
	sc->numports = IP175X_NUM_PORTS;
	sc->info.es_vlan_caps = ETHERSWITCH_VLAN_DOT1Q;

	device_printf(sc->sc_dev, "type: IP175D\n");
}