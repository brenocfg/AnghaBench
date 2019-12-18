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
typedef  int /*<<< orphan*/  uint16_t ;
struct rtl8366rb_softc {scalar_t__ phy4cpu; int /*<<< orphan*/ * vid; } ;
struct TYPE_3__ {size_t es_vlangroup; int es_member_ports; int es_untagged_ports; int /*<<< orphan*/  es_fid; int /*<<< orphan*/  es_vid; } ;
typedef  TYPE_1__ etherswitch_vlangroup_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  RTL8366_VMCR (int,size_t) ; 
 int /*<<< orphan*/  RTL8366_VMCR_FID (int /*<<< orphan*/ *) ; 
 int RTL8366_VMCR_MEMBER (int /*<<< orphan*/ *) ; 
 int RTL8366_VMCR_MULT ; 
 int RTL8366_VMCR_UNTAG (int /*<<< orphan*/ *) ; 
 struct rtl8366rb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_readreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rtl_getvgroup(device_t dev, etherswitch_vlangroup_t *vg)
{
	struct rtl8366rb_softc *sc;
	uint16_t vmcr[3];
	int i;
	int member, untagged;
	
	sc = device_get_softc(dev);

	for (i=0; i<RTL8366_VMCR_MULT; i++)
		vmcr[i] = rtl_readreg(dev, RTL8366_VMCR(i, vg->es_vlangroup));
		
	vg->es_vid = sc->vid[vg->es_vlangroup];
	member = RTL8366_VMCR_MEMBER(vmcr);
	untagged = RTL8366_VMCR_UNTAG(vmcr);
	if (sc->phy4cpu) {
		vg->es_member_ports = ((member & 0x20) >> 1) | (member & 0x0f);
		vg->es_untagged_ports = ((untagged & 0x20) >> 1) | (untagged & 0x0f);
	} else {
		vg->es_member_ports = member;
		vg->es_untagged_ports = untagged;
	}
	vg->es_fid = RTL8366_VMCR_FID(vmcr);
	return (0);
}