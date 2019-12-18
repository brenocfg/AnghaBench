#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct e6000sw_softc {int dummy; } ;
struct TYPE_3__ {int cmd; int /*<<< orphan*/  vlan_mode; } ;
typedef  TYPE_1__ etherswitch_conf_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  E6000SW_LOCK (struct e6000sw_softc*) ; 
 int /*<<< orphan*/  E6000SW_UNLOCK (struct e6000sw_softc*) ; 
 int ETHERSWITCH_CONF_VLAN_MODE ; 
 struct e6000sw_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e6000sw_set_vlan_mode (struct e6000sw_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
e6000sw_setconf(device_t dev, etherswitch_conf_t *conf)
{
	struct e6000sw_softc *sc;

	/* Set the VLAN mode. */
	sc = device_get_softc(dev);
	if (conf->cmd & ETHERSWITCH_CONF_VLAN_MODE) {
		E6000SW_LOCK(sc);
		e6000sw_set_vlan_mode(sc, conf->vlan_mode);
		E6000SW_UNLOCK(sc);
	}

	return (0);
}