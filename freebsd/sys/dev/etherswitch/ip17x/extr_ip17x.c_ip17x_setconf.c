#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* ip17x_set_vlan_mode ) (struct ip17x_softc*,int /*<<< orphan*/ ) ;} ;
struct ip17x_softc {TYPE_1__ hal; } ;
struct TYPE_5__ {int cmd; int /*<<< orphan*/  vlan_mode; } ;
typedef  TYPE_2__ etherswitch_conf_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ETHERSWITCH_CONF_VLAN_MODE ; 
 struct ip17x_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ip17x_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ip17x_setconf(device_t dev, etherswitch_conf_t *conf)
{
	struct ip17x_softc *sc;

	sc = device_get_softc(dev);

	/* Set the VLAN mode. */
	if (conf->cmd & ETHERSWITCH_CONF_VLAN_MODE)
		sc->hal.ip17x_set_vlan_mode(sc, conf->vlan_mode);

	return (0);
}