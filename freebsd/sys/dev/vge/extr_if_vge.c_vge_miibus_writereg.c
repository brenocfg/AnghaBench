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
struct vge_softc {int /*<<< orphan*/  vge_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CSR_READ_1 (struct vge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_SETBIT_1 (struct vge_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct vge_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct vge_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int EIO ; 
 int /*<<< orphan*/  VGE_MIIADDR ; 
 int /*<<< orphan*/  VGE_MIICMD ; 
 int VGE_MIICMD_WCMD ; 
 int /*<<< orphan*/  VGE_MIIDATA ; 
 int VGE_TIMEOUT ; 
 struct vge_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vge_miipoll_start (struct vge_softc*) ; 
 int /*<<< orphan*/  vge_miipoll_stop (struct vge_softc*) ; 

__attribute__((used)) static int
vge_miibus_writereg(device_t dev, int phy, int reg, int data)
{
	struct vge_softc *sc;
	int i, rval = 0;

	sc = device_get_softc(dev);

	vge_miipoll_stop(sc);

	/* Specify the register we want to write. */
	CSR_WRITE_1(sc, VGE_MIIADDR, reg);

	/* Specify the data we want to write. */
	CSR_WRITE_2(sc, VGE_MIIDATA, data);

	/* Issue write command. */
	CSR_SETBIT_1(sc, VGE_MIICMD, VGE_MIICMD_WCMD);

	/* Wait for the write command bit to self-clear. */
	for (i = 0; i < VGE_TIMEOUT; i++) {
		DELAY(1);
		if ((CSR_READ_1(sc, VGE_MIICMD) & VGE_MIICMD_WCMD) == 0)
			break;
	}

	if (i == VGE_TIMEOUT) {
		device_printf(sc->vge_dev, "MII write timed out\n");
		rval = EIO;
	}

	vge_miipoll_start(sc);

	return (rval);
}