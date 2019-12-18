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
struct adm6996fc_softc {scalar_t__ vlan_mode; } ;
struct TYPE_3__ {int cmd; scalar_t__ vlan_mode; } ;
typedef  TYPE_1__ etherswitch_conf_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ADM6996FC_READREG (int /*<<< orphan*/ ,int) ; 
 int ADM6996FC_SC3 ; 
 int ADM6996FC_TBV_SHIFT ; 
 int ADM6996FC_VF0H ; 
 int ADM6996FC_VF0L ; 
 int ADM6996FC_VV_SHIFT ; 
 int /*<<< orphan*/  ADM6996FC_WRITEREG (int /*<<< orphan*/ ,int,int) ; 
 int ETHERSWITCH_CONF_VLAN_MODE ; 
 scalar_t__ ETHERSWITCH_VLAN_DOT1Q ; 
 scalar_t__ ETHERSWITCH_VLAN_PORT ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct adm6996fc_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
adm6996fc_setconf(device_t dev, etherswitch_conf_t *conf)
{
	struct adm6996fc_softc	*sc;
	device_t		 parent;
	int 			 i;
	int 			 data;
	int	bcaddr[6] = {0x01, 0x03, 0x05, 0x07, 0x08, 0x09};

	sc = device_get_softc(dev);
	parent = device_get_parent(dev);

	if ((conf->cmd & ETHERSWITCH_CONF_VLAN_MODE) == 0)
		return (0);

	if (conf->vlan_mode == ETHERSWITCH_VLAN_PORT) {
		sc->vlan_mode = ETHERSWITCH_VLAN_PORT;
		data = ADM6996FC_READREG(parent, ADM6996FC_SC3);
		data &= ~(1 << ADM6996FC_TBV_SHIFT);
		ADM6996FC_WRITEREG(parent, ADM6996FC_SC3, data);
		for (i = 0;i <= 5; ++i) {
			data = ADM6996FC_READREG(parent, bcaddr[i]);
			data &= ~(0xf << 10);
			data |= (i << 10);
			ADM6996FC_WRITEREG(parent, bcaddr[i], data);
			ADM6996FC_WRITEREG(parent, ADM6996FC_VF0L + 2 * i,
			    0x003f);
			ADM6996FC_WRITEREG(parent, ADM6996FC_VF0H + 2 * i,
			    (1 << ADM6996FC_VV_SHIFT) | 1);
		}
	} else if (conf->vlan_mode == ETHERSWITCH_VLAN_DOT1Q) {
		sc->vlan_mode = ETHERSWITCH_VLAN_DOT1Q;
		data = ADM6996FC_READREG(parent, ADM6996FC_SC3);
		data |= (1 << ADM6996FC_TBV_SHIFT);
		ADM6996FC_WRITEREG(parent, ADM6996FC_SC3, data);
		for (i = 0;i <= 5; ++i) {
			data = ADM6996FC_READREG(parent, bcaddr[i]);
			/* Private VID set 1 */
			data &= ~(0xf << 10);
			data |= (1 << 10);
			ADM6996FC_WRITEREG(parent, bcaddr[i], data);
		}
		for (i = 2;i <= 15; ++i) {
			ADM6996FC_WRITEREG(parent, ADM6996FC_VF0H + 2 * i,
			    0x0000);
		}
	} else {
		/*
		 ADM6996FC have no VLAN off. Then set Port base and
		 add all port to member. Use VLAN Filter 1 is reset
		 default.
		 */
		sc->vlan_mode = 0;
		data = ADM6996FC_READREG(parent, ADM6996FC_SC3);
		data &= ~(1 << ADM6996FC_TBV_SHIFT);
		ADM6996FC_WRITEREG(parent, ADM6996FC_SC3, data);
		for (i = 0;i <= 5; ++i) {
			data = ADM6996FC_READREG(parent, bcaddr[i]);
			data &= ~(0xf << 10);
			data |= (1 << 10);
			if (i == 5)
				data &= ~(1 << 4);
			ADM6996FC_WRITEREG(parent, bcaddr[i], data);
		}
		/* default setting */
		ADM6996FC_WRITEREG(parent, ADM6996FC_VF0L + 2, 0x003f);
		ADM6996FC_WRITEREG(parent, ADM6996FC_VF0H + 2,
		    (1 << ADM6996FC_VV_SHIFT) | 1);
	}


	return (0);
}