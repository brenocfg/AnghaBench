#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rtl8366rb_softc {int* vid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int ETHERSWITCH_VID_VALID ; 
 int RTL8366_PVCR_PORT_MASK ; 
 int /*<<< orphan*/  RTL8366_PVCR_REG (int /*<<< orphan*/ ) ; 
 int RTL8366_PVCR_VAL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RTL8366_RCR ; 
 int RTL8366_RCR_HARD_RESET ; 
 int RTL8366_RCR_SOFT_RESET ; 
 int /*<<< orphan*/  RTL8366_SGCR ; 
 int RTL8366_SGCR_EN_VLAN ; 
 int RTL8366_SGCR_EN_VLAN_4KTB ; 
 int /*<<< orphan*/  RTL8366_VMCR (int /*<<< orphan*/ ,int) ; 
 int RTL8366_VMCR_MU_MEMBER_SHIFT ; 
 int /*<<< orphan*/  RTL8366_VMCR_MU_REG ; 
 int RTL8366_VMCR_MU_UNTAG_SHIFT ; 
 int /*<<< orphan*/  RTL_WAITOK ; 
 struct rtl8366rb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smi_rmw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rtl8366rb_init(device_t dev)
{
	struct rtl8366rb_softc *sc;
	int i;

	sc = device_get_softc(dev);

	/* Initialisation for TL-WR1043ND */
#ifdef RTL8366_SOFT_RESET
	smi_rmw(dev, RTL8366_RCR,
		RTL8366_RCR_SOFT_RESET,
		RTL8366_RCR_SOFT_RESET, RTL_WAITOK);
#else
	smi_rmw(dev, RTL8366_RCR,
		RTL8366_RCR_HARD_RESET,
		RTL8366_RCR_HARD_RESET, RTL_WAITOK);
#endif
	/* hard reset not return ack */
	DELAY(100000);
	/* Enable 16 VLAN mode */
	smi_rmw(dev, RTL8366_SGCR,
		RTL8366_SGCR_EN_VLAN | RTL8366_SGCR_EN_VLAN_4KTB,
		RTL8366_SGCR_EN_VLAN, RTL_WAITOK);
	/* Initialize our vlan table. */
	for (i = 0; i <= 1; i++)
		sc->vid[i] = (i + 1) | ETHERSWITCH_VID_VALID;
	/* Remove port 0 from VLAN 1. */
	smi_rmw(dev, RTL8366_VMCR(RTL8366_VMCR_MU_REG, 0),
		(1 << 0), 0, RTL_WAITOK);
	/* Add port 0 untagged and port 5 tagged to VLAN 2. */
	smi_rmw(dev, RTL8366_VMCR(RTL8366_VMCR_MU_REG, 1),
		((1 << 5 | 1 << 0) << RTL8366_VMCR_MU_MEMBER_SHIFT)
			| ((1 << 5 | 1 << 0) << RTL8366_VMCR_MU_UNTAG_SHIFT),
		((1 << 5 | 1 << 0) << RTL8366_VMCR_MU_MEMBER_SHIFT
			| ((1 << 0) << RTL8366_VMCR_MU_UNTAG_SHIFT)),
		RTL_WAITOK);
	/* Set PVID 2 for port 0. */
	smi_rmw(dev, RTL8366_PVCR_REG(0),
		RTL8366_PVCR_VAL(0, RTL8366_PVCR_PORT_MASK),
		RTL8366_PVCR_VAL(0, 1), RTL_WAITOK);
}