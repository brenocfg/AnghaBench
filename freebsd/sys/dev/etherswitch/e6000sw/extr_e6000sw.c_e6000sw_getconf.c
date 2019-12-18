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
struct e6000sw_softc {int /*<<< orphan*/  vlan_mode; } ;
struct TYPE_3__ {int /*<<< orphan*/  vlan_mode; int /*<<< orphan*/  cmd; } ;
typedef  TYPE_1__ etherswitch_conf_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ETHERSWITCH_CONF_VLAN_MODE ; 
 struct e6000sw_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
e6000sw_getconf(device_t dev, etherswitch_conf_t *conf)
{
	struct e6000sw_softc *sc;

	/* Return the VLAN mode. */
	sc = device_get_softc(dev);
	conf->cmd = ETHERSWITCH_CONF_VLAN_MODE;
	conf->vlan_mode = sc->vlan_mode;

	return (0);
}