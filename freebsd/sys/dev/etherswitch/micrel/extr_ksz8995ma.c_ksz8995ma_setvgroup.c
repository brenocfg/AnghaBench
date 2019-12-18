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
struct ksz8995ma_softc {scalar_t__ vlan_mode; } ;
struct TYPE_3__ {int es_vlangroup; int es_member_ports; int es_fid; int es_vid; } ;
typedef  TYPE_1__ etherswitch_vlangroup_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ ETHERSWITCH_VLAN_DOT1Q ; 
 scalar_t__ ETHERSWITCH_VLAN_PORT ; 
 scalar_t__ KSZ8995MA_IAC0 ; 
 scalar_t__ KSZ8995MA_IAC1 ; 
 scalar_t__ KSZ8995MA_IDR0 ; 
 scalar_t__ KSZ8995MA_IDR1 ; 
 scalar_t__ KSZ8995MA_IDR2 ; 
 scalar_t__ KSZ8995MA_PC1_BASE ; 
 int KSZ8995MA_PORT_SIZE ; 
 int KSZ8995MA_VLAN_TABLE_VALID ; 
 int KSZ8995MA_VLAN_TABLE_WRITE ; 
 struct ksz8995ma_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int ksz8995ma_readreg (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ksz8995ma_writereg (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int
ksz8995ma_setvgroup(device_t dev, etherswitch_vlangroup_t *vg)
{
	struct ksz8995ma_softc *sc;
	int data0;

	sc = device_get_softc(dev);

	if (sc->vlan_mode == ETHERSWITCH_VLAN_PORT) {
		data0 = ksz8995ma_readreg(dev, KSZ8995MA_PC1_BASE +
		    KSZ8995MA_PORT_SIZE * vg->es_vlangroup);
		ksz8995ma_writereg(dev, KSZ8995MA_PC1_BASE +
		    KSZ8995MA_PORT_SIZE * vg->es_vlangroup,
		    (data0 & 0xe0) | (vg->es_member_ports & 0x1f));
	} else if (sc->vlan_mode == ETHERSWITCH_VLAN_DOT1Q) {
		if (vg->es_member_ports != 0) {
			ksz8995ma_writereg(dev, KSZ8995MA_IDR2,
			    KSZ8995MA_VLAN_TABLE_VALID |
			    (vg->es_member_ports & 0x1f));
			ksz8995ma_writereg(dev, KSZ8995MA_IDR1,
			    vg->es_fid << 4 | vg->es_vid >> 8);
			ksz8995ma_writereg(dev, KSZ8995MA_IDR0,
			    vg->es_vid & 0xff);
		} else {
			ksz8995ma_writereg(dev, KSZ8995MA_IDR2, 0);
			ksz8995ma_writereg(dev, KSZ8995MA_IDR1, 0);
			ksz8995ma_writereg(dev, KSZ8995MA_IDR0, 0);
		}
		ksz8995ma_writereg(dev, KSZ8995MA_IAC0,
		    KSZ8995MA_VLAN_TABLE_WRITE);
		ksz8995ma_writereg(dev, KSZ8995MA_IAC1, vg->es_vlangroup);
	}

	return (0);
}