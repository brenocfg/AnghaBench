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
struct TYPE_4__ {int (* arswitch_hw_get_switch_macaddr ) (struct arswitch_softc*,int /*<<< orphan*/ *) ;} ;
struct arswitch_softc {TYPE_1__ hal; int /*<<< orphan*/  vlan_mode; } ;
struct TYPE_5__ {int /*<<< orphan*/  cmd; int /*<<< orphan*/  switch_macaddr; int /*<<< orphan*/  vlan_mode; } ;
typedef  TYPE_2__ etherswitch_conf_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ETHERSWITCH_CONF_SWITCH_MACADDR ; 
 int /*<<< orphan*/  ETHERSWITCH_CONF_VLAN_MODE ; 
 struct arswitch_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int stub1 (struct arswitch_softc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
arswitch_getconf(device_t dev, etherswitch_conf_t *conf)
{
	struct arswitch_softc *sc;
	int ret;

	sc = device_get_softc(dev);

	/* Return the VLAN mode. */
	conf->cmd = ETHERSWITCH_CONF_VLAN_MODE;
	conf->vlan_mode = sc->vlan_mode;

	/* Return the switch ethernet address. */
	ret = sc->hal.arswitch_hw_get_switch_macaddr(sc,
	    &conf->switch_macaddr);
	if (ret == 0) {
		conf->cmd |= ETHERSWITCH_CONF_SWITCH_MACADDR;
	}

	return (0);
}