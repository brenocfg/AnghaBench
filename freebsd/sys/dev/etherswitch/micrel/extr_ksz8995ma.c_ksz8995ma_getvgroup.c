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
struct ksz8995ma_softc {scalar_t__ vlan_mode; scalar_t__ numports; } ;
struct TYPE_3__ {scalar_t__ es_vlangroup; int es_vid; int es_member_ports; int es_untagged_ports; int es_fid; } ;
typedef  TYPE_1__ etherswitch_vlangroup_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 void* ETHERSWITCH_VID_VALID ; 
 scalar_t__ ETHERSWITCH_VLAN_DOT1Q ; 
 scalar_t__ ETHERSWITCH_VLAN_PORT ; 
 int /*<<< orphan*/  KSZ8995MA_IAC0 ; 
 int /*<<< orphan*/  KSZ8995MA_IAC1 ; 
 scalar_t__ KSZ8995MA_IDR0 ; 
 scalar_t__ KSZ8995MA_IDR1 ; 
 scalar_t__ KSZ8995MA_IDR2 ; 
 scalar_t__ KSZ8995MA_PC1_BASE ; 
 int KSZ8995MA_PORT_SIZE ; 
 int KSZ8995MA_VLAN_TABLE_READ ; 
 int KSZ8995MA_VLAN_TABLE_VALID ; 
 struct ksz8995ma_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int ksz8995ma_readreg (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ksz8995ma_writereg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ksz8995ma_getvgroup(device_t dev, etherswitch_vlangroup_t *vg)
{
	int data0, data1, data2;
	int vlantab;
	struct ksz8995ma_softc *sc;

	sc = device_get_softc(dev);

	if (sc->vlan_mode == ETHERSWITCH_VLAN_PORT) {
		if (vg->es_vlangroup < sc->numports) {
			vg->es_vid = ETHERSWITCH_VID_VALID;
			vg->es_vid |= vg->es_vlangroup;
			data0 = ksz8995ma_readreg(dev, KSZ8995MA_PC1_BASE +
			    KSZ8995MA_PORT_SIZE * vg->es_vlangroup);
			vg->es_member_ports = data0 & 0x1f;
			vg->es_untagged_ports = vg->es_member_ports;
			vg->es_fid = 0;
		} else {
			vg->es_vid = 0;
		}
	} else if (sc->vlan_mode == ETHERSWITCH_VLAN_DOT1Q) {
		ksz8995ma_writereg(dev, KSZ8995MA_IAC0,
		    KSZ8995MA_VLAN_TABLE_READ);
		ksz8995ma_writereg(dev, KSZ8995MA_IAC1, vg->es_vlangroup);
		data2 = ksz8995ma_readreg(dev, KSZ8995MA_IDR2);
		data1 = ksz8995ma_readreg(dev, KSZ8995MA_IDR1);
		data0 = ksz8995ma_readreg(dev, KSZ8995MA_IDR0);
		vlantab = data2 << 16 | data1 << 8 | data0;
		if (data2 & KSZ8995MA_VLAN_TABLE_VALID) {
			vg->es_vid = ETHERSWITCH_VID_VALID;
			vg->es_vid |= vlantab & 0xfff;
			vg->es_member_ports = (vlantab >> 16) & 0x1f;
			vg->es_untagged_ports = vg->es_member_ports;
			vg->es_fid = (vlantab >> 12) & 0x0f;
		} else {
			vg->es_fid = 0;
		}
	}
	
	return (0);
}