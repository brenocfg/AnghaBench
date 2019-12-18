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
struct mii_softc {int mii_capabilities; int mii_capmask; int /*<<< orphan*/  mii_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BMSR_100TXFDX ; 
 int /*<<< orphan*/  MIIBUS_MEDIAINIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIIBUS_WRITEREG (int /*<<< orphan*/ ,int,int,int) ; 
 int MIIF_NOISOLATE ; 
 int MIIF_NOMANPAUSE ; 
 struct mii_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mii_phy_add_media (struct mii_softc*) ; 
 int /*<<< orphan*/  mii_phy_dev_attach (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  rlswitch_funcs ; 
 int /*<<< orphan*/  rlswitch_phydump (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rlswitch_attach(device_t dev)
{
	struct mii_softc	*sc;

	sc = device_get_softc(dev);

	/*
	 * We handle all pseudo PHYs in a single instance.
	 */
	mii_phy_dev_attach(dev, MIIF_NOISOLATE | MIIF_NOMANPAUSE,
	    &rlswitch_funcs, 0);

	sc->mii_capabilities = BMSR_100TXFDX & sc->mii_capmask;
	device_printf(dev, " ");
	mii_phy_add_media(sc);
	printf("\n");
#ifdef RL_DEBUG
	rlswitch_phydump(dev);
#endif
	
#ifdef RL_VLAN
	int val;

	/* Global Control 0 */
	val = 0;
	val |= 0 << 10;		/* enable 802.1q VLAN Tag support */
	val |= 0 << 9;		/* enable VLAN ingress filtering */
	val |= 1 << 8;		/* disable VLAN tag admit control */
	val |= 1 << 6;		/* internal use */
	val |= 1 << 5;		/* internal use */
	val |= 1 << 4;		/* internal use */
	val |= 1 << 3;		/* internal use */
	val |= 1 << 1;		/* reserved */
	MIIBUS_WRITEREG(sc->mii_dev, 0, 16, val);

	/* Global Control 2 */
	val = 0;
	val |= 1 << 15;		/* reserved */
	val |= 0 << 14;		/* enable 1552 Bytes support */
	val |= 1 << 13;		/* enable broadcast input drop */
	val |= 1 << 12;		/* forward reserved control frames */
	val |= 1 << 11;		/* disable forwarding unicast frames to other VLAN's */
	val |= 1 << 10;		/* disable forwarding ARP broadcasts to other VLAN's */
	val |= 1 << 9;		/* enable 48 pass 1 */
	val |= 0 << 8;		/* enable VLAN */
	val |= 1 << 7;		/* reserved */
	val |= 1 << 6;		/* enable defer */
	val |= 1 << 5;		/* 43ms LED blink time */
	val |= 3 << 3;		/* 16:1 queue weight */
	val |= 1 << 2;		/* disable broadcast storm control */
	val |= 1 << 1;		/* enable power-on LED blinking */
	val |= 1 << 0;		/* reserved */
	MIIBUS_WRITEREG(sc->mii_dev, 0, 18, val);

	/* Port 0 Control Register 0 */
	val = 0;
	val |= 1 << 15;		/* reserved */
	val |= 1 << 11;		/* drop received packets with wrong VLAN tag */
	val |= 1 << 10;		/* disable 802.1p priority classification */
	val |= 1 << 9;		/* disable diffserv priority classification */
	val |= 1 << 6;		/* internal use */
	val |= 3 << 4;		/* internal use */
	val |= 1 << 3;		/* internal use */
	val |= 1 << 2;		/* internal use */
	val |= 1 << 0;		/* remove VLAN tags on output */
	MIIBUS_WRITEREG(sc->mii_dev, 0, 22, val);

	/* Port 1 Control Register 0 */
	val = 0;
	val |= 1 << 15;		/* reserved */
	val |= 1 << 11;		/* drop received packets with wrong VLAN tag */
	val |= 1 << 10;		/* disable 802.1p priority classification */
	val |= 1 << 9;		/* disable diffserv priority classification */
	val |= 1 << 6;		/* internal use */
	val |= 3 << 4;		/* internal use */
	val |= 1 << 3;		/* internal use */
	val |= 1 << 2;		/* internal use */
	val |= 1 << 0;		/* remove VLAN tags on output */
	MIIBUS_WRITEREG(sc->mii_dev, 1, 22, val);

	/* Port 2 Control Register 0 */
	val = 0;
	val |= 1 << 15;		/* reserved */
	val |= 1 << 11;		/* drop received packets with wrong VLAN tag */
	val |= 1 << 10;		/* disable 802.1p priority classification */
	val |= 1 << 9;		/* disable diffserv priority classification */
	val |= 1 << 6;		/* internal use */
	val |= 3 << 4;		/* internal use */
	val |= 1 << 3;		/* internal use */
	val |= 1 << 2;		/* internal use */
	val |= 1 << 0;		/* remove VLAN tags on output */
	MIIBUS_WRITEREG(sc->mii_dev, 2, 22, val);

	/* Port 3 Control Register 0 */
	val = 0;
	val |= 1 << 15;		/* reserved */
	val |= 1 << 11;		/* drop received packets with wrong VLAN tag */
	val |= 1 << 10;		/* disable 802.1p priority classification */
	val |= 1 << 9;		/* disable diffserv priority classification */
	val |= 1 << 6;		/* internal use */
	val |= 3 << 4;		/* internal use */
	val |= 1 << 3;		/* internal use */
	val |= 1 << 2;		/* internal use */
	val |= 1 << 0;		/* remove VLAN tags on output */
	MIIBUS_WRITEREG(sc->mii_dev, 3, 22, val);

	/* Port 4 (system port) Control Register 0 */
	val = 0;
	val |= 1 << 15;		/* reserved */
	val |= 0 << 11;		/* don't drop received packets with wrong VLAN tag */
	val |= 1 << 10;		/* disable 802.1p priority classification */
	val |= 1 << 9;		/* disable diffserv priority classification */
	val |= 1 << 6;		/* internal use */
	val |= 3 << 4;		/* internal use */
	val |= 1 << 3;		/* internal use */
	val |= 1 << 2;		/* internal use */
	val |= 2 << 0;		/* add VLAN tags for untagged packets on output */
	MIIBUS_WRITEREG(sc->mii_dev, 4, 22, val);

	/* Port 0 Control Register 1 and VLAN A */
	val = 0;
	val |= 0x0 << 12;	/* Port 0 VLAN Index */
	val |= 1 << 11;		/* internal use */
	val |= 1 << 10;		/* internal use */
	val |= 1 << 9;		/* internal use */
	val |= 1 << 7;		/* internal use */
	val |= 1 << 6;		/* internal use */
	val |= 0x11 << 0;	/* VLAN A membership */
	MIIBUS_WRITEREG(sc->mii_dev, 0, 24, val);

	/* Port 0 Control Register 2 and VLAN A */
	val = 0;
	val |= 1 << 15;		/* internal use */
	val |= 1 << 14;		/* internal use */
	val |= 1 << 13;		/* internal use */
	val |= 1 << 12;		/* internal use */
	val |= 0x100 << 0;	/* VLAN A ID */
	MIIBUS_WRITEREG(sc->mii_dev, 0, 25, val);

	/* Port 1 Control Register 1 and VLAN B */
	val = 0;
	val |= 0x1 << 12;	/* Port 1 VLAN Index */
	val |= 1 << 11;		/* internal use */
	val |= 1 << 10;		/* internal use */
	val |= 1 << 9;		/* internal use */
	val |= 1 << 7;		/* internal use */
	val |= 1 << 6;		/* internal use */
	val |= 0x12 << 0;	/* VLAN B membership */
	MIIBUS_WRITEREG(sc->mii_dev, 1, 24, val);

	/* Port 1 Control Register 2 and VLAN B */
	val = 0;
	val |= 1 << 15;		/* internal use */
	val |= 1 << 14;		/* internal use */
	val |= 1 << 13;		/* internal use */
	val |= 1 << 12;		/* internal use */
	val |= 0x101 << 0;	/* VLAN B ID */
	MIIBUS_WRITEREG(sc->mii_dev, 1, 25, val);

	/* Port 2 Control Register 1 and VLAN C */
	val = 0;
	val |= 0x2 << 12;	/* Port 2 VLAN Index */
	val |= 1 << 11;		/* internal use */
	val |= 1 << 10;		/* internal use */
	val |= 1 << 9;		/* internal use */
	val |= 1 << 7;		/* internal use */
	val |= 1 << 6;		/* internal use */
	val |= 0x14 << 0;	/* VLAN C membership */
	MIIBUS_WRITEREG(sc->mii_dev, 2, 24, val);

	/* Port 2 Control Register 2 and VLAN C */
	val = 0;
	val |= 1 << 15;		/* internal use */
	val |= 1 << 14;		/* internal use */
	val |= 1 << 13;		/* internal use */
	val |= 1 << 12;		/* internal use */
	val |= 0x102 << 0;	/* VLAN C ID */
	MIIBUS_WRITEREG(sc->mii_dev, 2, 25, val);

	/* Port 3 Control Register 1 and VLAN D */
	val = 0;
	val |= 0x3 << 12;	/* Port 3 VLAN Index */
	val |= 1 << 11;		/* internal use */
	val |= 1 << 10;		/* internal use */
	val |= 1 << 9;		/* internal use */
	val |= 1 << 7;		/* internal use */
	val |= 1 << 6;		/* internal use */
	val |= 0x18 << 0;	/* VLAN D membership */
	MIIBUS_WRITEREG(sc->mii_dev, 3, 24, val);

	/* Port 3 Control Register 2 and VLAN D */
	val = 0;
	val |= 1 << 15;		/* internal use */
	val |= 1 << 14;		/* internal use */
	val |= 1 << 13;		/* internal use */
	val |= 1 << 12;		/* internal use */
	val |= 0x103 << 0;	/* VLAN D ID */
	MIIBUS_WRITEREG(sc->mii_dev, 3, 25, val);

	/* Port 4 Control Register 1 and VLAN E */
	val = 0;
	val |= 0x0 << 12;	/* Port 4 VLAN Index */
	val |= 1 << 11;		/* internal use */
	val |= 1 << 10;		/* internal use */
	val |= 1 << 9;		/* internal use */
	val |= 1 << 7;		/* internal use */
	val |= 1 << 6;		/* internal use */
	val |= 0 << 0;		/* VLAN E membership */
	MIIBUS_WRITEREG(sc->mii_dev, 4, 24, val);

	/* Port 4 Control Register 2 and VLAN E */
	val = 0;
	val |= 1 << 15;		/* internal use */
	val |= 1 << 14;		/* internal use */
	val |= 1 << 13;		/* internal use */
	val |= 1 << 12;		/* internal use */
	val |= 0x104 << 0;	/* VLAN E ID */
	MIIBUS_WRITEREG(sc->mii_dev, 4, 25, val);
#endif

#ifdef RL_DEBUG
	rlswitch_phydump(dev);
#endif
	MIIBUS_MEDIAINIT(sc->mii_dev);
	return (0);
}