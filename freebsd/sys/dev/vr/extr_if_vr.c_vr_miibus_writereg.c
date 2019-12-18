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
struct vr_softc {int /*<<< orphan*/  vr_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CSR_READ_1 (struct vr_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct vr_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct vr_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  VR_MIIADDR ; 
 int /*<<< orphan*/  VR_MIICMD ; 
 int VR_MIICMD_WRITE_ENB ; 
 int /*<<< orphan*/  VR_MIIDATA ; 
 int VR_MII_TIMEOUT ; 
 int /*<<< orphan*/  VR_SETBIT (struct vr_softc*,int /*<<< orphan*/ ,int) ; 
 struct vr_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static int
vr_miibus_writereg(device_t dev, int phy, int reg, int data)
{
	struct vr_softc		*sc;
	int			i;

	sc = device_get_softc(dev);

	/* Set the register address and data to write. */
	CSR_WRITE_1(sc, VR_MIIADDR, reg);
	CSR_WRITE_2(sc, VR_MIIDATA, data);
	VR_SETBIT(sc, VR_MIICMD, VR_MIICMD_WRITE_ENB);

	for (i = 0; i < VR_MII_TIMEOUT; i++) {
		DELAY(1);
		if ((CSR_READ_1(sc, VR_MIICMD) & VR_MIICMD_WRITE_ENB) == 0)
			break;
	}
	if (i == VR_MII_TIMEOUT)
		device_printf(sc->vr_dev, "phy write timeout %d:%d\n", phy,
		    reg);

	return (0);
}