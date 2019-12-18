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
typedef  int u_int32_t ;
struct hme_softc {int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_SPACE_BARRIER_READ ; 
 int BUS_SPACE_BARRIER_WRITE ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  HME_MIFI_CFG ; 
 int /*<<< orphan*/  HME_MIFI_FO ; 
 int /*<<< orphan*/  HME_MIF_BARRIER (struct hme_softc*,int /*<<< orphan*/ ,int,int) ; 
 int HME_MIF_CFG_PHY ; 
 int HME_MIF_FO_DATA ; 
 int HME_MIF_FO_OPC_SHIFT ; 
 int HME_MIF_FO_PHYAD_SHIFT ; 
 int HME_MIF_FO_REGAD_SHIFT ; 
 int HME_MIF_FO_ST_SHIFT ; 
 int HME_MIF_FO_TALSB ; 
 int HME_MIF_FO_TAMSB ; 
 int HME_MIF_READ_4 (struct hme_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HME_MIF_WRITE_4 (struct hme_softc*,int /*<<< orphan*/ ,int) ; 
 int HME_PHYAD_EXTERNAL ; 
 int MII_COMMAND_START ; 
 int MII_COMMAND_WRITE ; 
 struct hme_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

int
hme_mii_writereg(device_t dev, int phy, int reg, int val)
{
	struct hme_softc *sc;
	int n;
	u_int32_t v;

	sc = device_get_softc(dev);
	/* Select the desired PHY in the MIF configuration register */
	v = HME_MIF_READ_4(sc, HME_MIFI_CFG);
	if (phy == HME_PHYAD_EXTERNAL)
		v |= HME_MIF_CFG_PHY;
	else
		v &= ~HME_MIF_CFG_PHY;
	HME_MIF_WRITE_4(sc, HME_MIFI_CFG, v);

	/* Construct the frame command */
	v = (MII_COMMAND_START << HME_MIF_FO_ST_SHIFT)	|
	    HME_MIF_FO_TAMSB				|
	    (MII_COMMAND_WRITE << HME_MIF_FO_OPC_SHIFT)	|
	    (phy << HME_MIF_FO_PHYAD_SHIFT)		|
	    (reg << HME_MIF_FO_REGAD_SHIFT)		|
	    (val & HME_MIF_FO_DATA);

	HME_MIF_WRITE_4(sc, HME_MIFI_FO, v);
	HME_MIF_BARRIER(sc, HME_MIFI_FO, 4,
	    BUS_SPACE_BARRIER_READ | BUS_SPACE_BARRIER_WRITE);
	for (n = 0; n < 100; n++) {
		DELAY(1);
		v = HME_MIF_READ_4(sc, HME_MIFI_FO);
		if (v & HME_MIF_FO_TALSB)
			return (1);
	}

	device_printf(sc->sc_dev, "mii_write timeout\n");
	return (0);
}