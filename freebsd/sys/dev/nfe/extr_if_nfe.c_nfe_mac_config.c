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
typedef  int uint32_t ;
struct nfe_softc {int nfe_flags; } ;
struct mii_data {int /*<<< orphan*/  mii_media_active; } ;

/* Variables and functions */
#define  IFM_1000_T 130 
#define  IFM_100_TX 129 
#define  IFM_10_T 128 
 int IFM_ETH_RXPAUSE ; 
 int IFM_ETH_TXPAUSE ; 
 int IFM_FDX ; 
 int IFM_OPTIONS (int /*<<< orphan*/ ) ; 
 int const IFM_SUBTYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFE_LINKSPEED ; 
 int /*<<< orphan*/  NFE_LOCK_ASSERT (struct nfe_softc*) ; 
 int NFE_MEDIA_1000T ; 
 int NFE_MEDIA_100TX ; 
 int NFE_MEDIA_10T ; 
 int NFE_MEDIA_SET ; 
 int /*<<< orphan*/  NFE_MISC1 ; 
 int NFE_MISC1_HDX ; 
 int NFE_MISC1_MAGIC ; 
 int NFE_MISC1_TX_PAUSE ; 
 int NFE_PFF_RX_PAUSE ; 
 int NFE_PHY_1000T ; 
 int NFE_PHY_100TX ; 
 int NFE_PHY_HDX ; 
 int /*<<< orphan*/  NFE_PHY_IFACE ; 
 int NFE_R1_MAGIC_1000 ; 
 int NFE_R1_MAGIC_10_100 ; 
 int NFE_R1_MAGIC_DEFAULT ; 
 int NFE_READ (struct nfe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFE_RNDSEED ; 
 int /*<<< orphan*/  NFE_RXFILTER ; 
 int NFE_SEED_1000T ; 
 int NFE_SEED_100TX ; 
 int NFE_SEED_10T ; 
 int NFE_SEED_MASK ; 
 int /*<<< orphan*/  NFE_SETUP_R1 ; 
 int NFE_TX_FLOW_CTRL ; 
 int /*<<< orphan*/  NFE_TX_PAUSE_FRAME ; 
 int NFE_TX_PAUSE_FRAME_DISABLE ; 
 int NFE_TX_PAUSE_FRAME_ENABLE ; 
 int /*<<< orphan*/  NFE_WRITE (struct nfe_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
nfe_mac_config(struct nfe_softc *sc, struct mii_data *mii)
{
	uint32_t link, misc, phy, seed;
	uint32_t val;

	NFE_LOCK_ASSERT(sc);

	phy = NFE_READ(sc, NFE_PHY_IFACE);
	phy &= ~(NFE_PHY_HDX | NFE_PHY_100TX | NFE_PHY_1000T);

	seed = NFE_READ(sc, NFE_RNDSEED);
	seed &= ~NFE_SEED_MASK;

	misc = NFE_MISC1_MAGIC;
	link = NFE_MEDIA_SET;

	if ((IFM_OPTIONS(mii->mii_media_active) & IFM_FDX) == 0) {
		phy  |= NFE_PHY_HDX;	/* half-duplex */
		misc |= NFE_MISC1_HDX;
	}

	switch (IFM_SUBTYPE(mii->mii_media_active)) {
	case IFM_1000_T:	/* full-duplex only */
		link |= NFE_MEDIA_1000T;
		seed |= NFE_SEED_1000T;
		phy  |= NFE_PHY_1000T;
		break;
	case IFM_100_TX:
		link |= NFE_MEDIA_100TX;
		seed |= NFE_SEED_100TX;
		phy  |= NFE_PHY_100TX;
		break;
	case IFM_10_T:
		link |= NFE_MEDIA_10T;
		seed |= NFE_SEED_10T;
		break;
	}

	if ((phy & 0x10000000) != 0) {
		if (IFM_SUBTYPE(mii->mii_media_active) == IFM_1000_T)
			val = NFE_R1_MAGIC_1000;
		else
			val = NFE_R1_MAGIC_10_100;
	} else
		val = NFE_R1_MAGIC_DEFAULT;
	NFE_WRITE(sc, NFE_SETUP_R1, val);

	NFE_WRITE(sc, NFE_RNDSEED, seed);	/* XXX: gigabit NICs only? */

	NFE_WRITE(sc, NFE_PHY_IFACE, phy);
	NFE_WRITE(sc, NFE_MISC1, misc);
	NFE_WRITE(sc, NFE_LINKSPEED, link);

	if ((IFM_OPTIONS(mii->mii_media_active) & IFM_FDX) != 0) {
		/* It seems all hardwares supports Rx pause frames. */
		val = NFE_READ(sc, NFE_RXFILTER);
		if ((IFM_OPTIONS(mii->mii_media_active) &
		    IFM_ETH_RXPAUSE) != 0)
			val |= NFE_PFF_RX_PAUSE;
		else
			val &= ~NFE_PFF_RX_PAUSE;
		NFE_WRITE(sc, NFE_RXFILTER, val);
		if ((sc->nfe_flags & NFE_TX_FLOW_CTRL) != 0) {
			val = NFE_READ(sc, NFE_MISC1);
			if ((IFM_OPTIONS(mii->mii_media_active) &
			    IFM_ETH_TXPAUSE) != 0) {
				NFE_WRITE(sc, NFE_TX_PAUSE_FRAME,
				    NFE_TX_PAUSE_FRAME_ENABLE);
				val |= NFE_MISC1_TX_PAUSE;
			} else {
				val &= ~NFE_MISC1_TX_PAUSE;
				NFE_WRITE(sc, NFE_TX_PAUSE_FRAME,
				    NFE_TX_PAUSE_FRAME_DISABLE);
			}
			NFE_WRITE(sc, NFE_MISC1, val);
		}
	} else {
		/* disable rx/tx pause frames */
		val = NFE_READ(sc, NFE_RXFILTER);
		val &= ~NFE_PFF_RX_PAUSE;
		NFE_WRITE(sc, NFE_RXFILTER, val);
		if ((sc->nfe_flags & NFE_TX_FLOW_CTRL) != 0) {
			NFE_WRITE(sc, NFE_TX_PAUSE_FRAME,
			    NFE_TX_PAUSE_FRAME_DISABLE);
			val = NFE_READ(sc, NFE_MISC1);
			val &= ~NFE_MISC1_TX_PAUSE;
			NFE_WRITE(sc, NFE_MISC1, val);
		}
	}
}