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
struct mtkswitch_softc {int dummy; } ;
struct TYPE_3__ {int cmd; int /*<<< orphan*/  vlan_mode; } ;
typedef  TYPE_1__ etherswitch_conf_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ETHERSWITCH_CONF_VLAN_MODE ; 
 struct mtkswitch_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int mtkswitch_set_vlan_mode (struct mtkswitch_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mtkswitch_setconf(device_t dev, etherswitch_conf_t *conf)
{
	struct mtkswitch_softc *sc;
	int err;
        
	sc = device_get_softc(dev);
        
	/* Set the VLAN mode. */
	if (conf->cmd & ETHERSWITCH_CONF_VLAN_MODE) {
		err = mtkswitch_set_vlan_mode(sc, conf->vlan_mode);
		if (err != 0)
			return (err);
	}

	return (0);
}