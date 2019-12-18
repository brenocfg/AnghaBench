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
struct rtl8366rb_softc {int* vid; scalar_t__ chip_type; scalar_t__ phy4cpu; } ;
struct TYPE_3__ {int es_vlangroup; int es_vid; int es_member_ports; int es_untagged_ports; int es_fid; } ;
typedef  TYPE_1__ etherswitch_vlangroup_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ETHERSWITCH_VID_VALID ; 
 scalar_t__ RTL8366RB ; 
 int /*<<< orphan*/  RTL8366_VMCR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RTL8366_VMCR_DOT1Q_REG ; 
 int RTL8366_VMCR_DOT1Q_VID_MASK ; 
 int RTL8366_VMCR_DOT1Q_VID_SHIFT ; 
 int RTL8366_VMCR_FID_FID_MASK ; 
 int RTL8366_VMCR_FID_FID_SHIFT ; 
 int /*<<< orphan*/  RTL8366_VMCR_FID_REG ; 
 int RTL8366_VMCR_MU_MEMBER_MASK ; 
 int RTL8366_VMCR_MU_MEMBER_SHIFT ; 
 int /*<<< orphan*/  RTL8366_VMCR_MU_REG ; 
 int RTL8366_VMCR_MU_UNTAG_MASK ; 
 int RTL8366_VMCR_MU_UNTAG_SHIFT ; 
 struct rtl8366rb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_writereg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
rtl_setvgroup(device_t dev, etherswitch_vlangroup_t *vg)
{
	struct rtl8366rb_softc *sc;
	int g;
	int member, untagged;

	sc = device_get_softc(dev);

	g = vg->es_vlangroup;

	sc->vid[g] = vg->es_vid;
	/* VLAN group disabled ? */
	if (vg->es_member_ports == 0 && vg->es_untagged_ports == 0 && vg->es_vid == 0)
		return (0);
	sc->vid[g] |= ETHERSWITCH_VID_VALID;
	rtl_writereg(dev, RTL8366_VMCR(RTL8366_VMCR_DOT1Q_REG, g),
		(vg->es_vid << RTL8366_VMCR_DOT1Q_VID_SHIFT) & RTL8366_VMCR_DOT1Q_VID_MASK);
	if (sc->phy4cpu) {
		/* add space at phy4 */
		member = (vg->es_member_ports & 0x0f) |
		    ((vg->es_member_ports & 0x10) << 1);
		untagged = (vg->es_untagged_ports & 0x0f) |
		    ((vg->es_untagged_ports & 0x10) << 1);
	} else {
		member = vg->es_member_ports;
		untagged = vg->es_untagged_ports;
	}
	if (sc->chip_type == RTL8366RB) {
		rtl_writereg(dev, RTL8366_VMCR(RTL8366_VMCR_MU_REG, g),
	 	    ((member << RTL8366_VMCR_MU_MEMBER_SHIFT) & RTL8366_VMCR_MU_MEMBER_MASK) |
		    ((untagged << RTL8366_VMCR_MU_UNTAG_SHIFT) & RTL8366_VMCR_MU_UNTAG_MASK));
		rtl_writereg(dev, RTL8366_VMCR(RTL8366_VMCR_FID_REG, g),
		    vg->es_fid);
	} else {
		rtl_writereg(dev, RTL8366_VMCR(RTL8366_VMCR_MU_REG, g),
		    ((member << RTL8366_VMCR_MU_MEMBER_SHIFT) & RTL8366_VMCR_MU_MEMBER_MASK) |
		    ((untagged << RTL8366_VMCR_MU_UNTAG_SHIFT) & RTL8366_VMCR_MU_UNTAG_MASK) |
		    ((vg->es_fid << RTL8366_VMCR_FID_FID_SHIFT) & RTL8366_VMCR_FID_FID_MASK));
	}
	return (0);
}