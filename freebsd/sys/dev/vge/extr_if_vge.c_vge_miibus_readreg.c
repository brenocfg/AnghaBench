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
typedef  int uint16_t ;
struct vge_softc {int /*<<< orphan*/  vge_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CSR_READ_1 (struct vge_softc*,int /*<<< orphan*/ ) ; 
 int CSR_READ_2 (struct vge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_SETBIT_1 (struct vge_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct vge_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  VGE_MIIADDR ; 
 int /*<<< orphan*/  VGE_MIICMD ; 
 int VGE_MIICMD_RCMD ; 
 int /*<<< orphan*/  VGE_MIIDATA ; 
 int VGE_TIMEOUT ; 
 struct vge_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vge_miipoll_start (struct vge_softc*) ; 
 int /*<<< orphan*/  vge_miipoll_stop (struct vge_softc*) ; 

__attribute__((used)) static int
vge_miibus_readreg(device_t dev, int phy, int reg)
{
	struct vge_softc *sc;
	int i;
	uint16_t rval = 0;

	sc = device_get_softc(dev);

	vge_miipoll_stop(sc);

	/* Specify the register we want to read. */
	CSR_WRITE_1(sc, VGE_MIIADDR, reg);

	/* Issue read command. */
	CSR_SETBIT_1(sc, VGE_MIICMD, VGE_MIICMD_RCMD);

	/* Wait for the read command bit to self-clear. */
	for (i = 0; i < VGE_TIMEOUT; i++) {
		DELAY(1);
		if ((CSR_READ_1(sc, VGE_MIICMD) & VGE_MIICMD_RCMD) == 0)
			break;
	}

	if (i == VGE_TIMEOUT)
		device_printf(sc->vge_dev, "MII read timed out\n");
	else
		rval = CSR_READ_2(sc, VGE_MIIDATA);

	vge_miipoll_start(sc);

	return (rval);
}