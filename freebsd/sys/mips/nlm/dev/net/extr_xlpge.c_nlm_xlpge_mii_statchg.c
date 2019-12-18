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
struct nlm_xlpge_softc {int block; int port; int /*<<< orphan*/  duplexity; int /*<<< orphan*/  speed; int /*<<< orphan*/  base_addr; int /*<<< orphan*/ * mii_bus; } ;
struct mii_data {int mii_media_status; int mii_media_active; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 scalar_t__ IFM_100_TX ; 
 scalar_t__ IFM_10_T ; 
 int IFM_ACTIVE ; 
 int IFM_FDX ; 
 int IFM_GMASK ; 
 scalar_t__ IFM_SUBTYPE (int) ; 
 int /*<<< orphan*/  NLM_SGMII_DUPLEX_FULL ; 
 int /*<<< orphan*/  NLM_SGMII_DUPLEX_HALF ; 
 int /*<<< orphan*/  NLM_SGMII_SPEED_10 ; 
 int /*<<< orphan*/  NLM_SGMII_SPEED_100 ; 
 int /*<<< orphan*/  NLM_SGMII_SPEED_1000 ; 
 void* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlm_nae_setup_mac (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int,char*,char*) ; 

__attribute__((used)) static void
nlm_xlpge_mii_statchg(device_t dev)
{
	struct nlm_xlpge_softc *sc;
	struct mii_data *mii;
	char *speed, *duplexity;

	sc = device_get_softc(dev);
	if (sc->mii_bus == NULL)
		return;

	mii = device_get_softc(sc->mii_bus);
	if (mii->mii_media_status & IFM_ACTIVE) {
		if (IFM_SUBTYPE(mii->mii_media_active) ==  IFM_10_T) {
			sc->speed = NLM_SGMII_SPEED_10;
			speed =  "10Mbps";
		} else if (IFM_SUBTYPE(mii->mii_media_active) == IFM_100_TX) {
			sc->speed = NLM_SGMII_SPEED_100;
			speed = "100Mbps";
		} else { /* default to 1G */
			sc->speed = NLM_SGMII_SPEED_1000;
			speed =  "1Gbps";
		}

		if ((mii->mii_media_active & IFM_GMASK) == IFM_FDX) {
			sc->duplexity = NLM_SGMII_DUPLEX_FULL;
			duplexity =  "full";
		} else {
			sc->duplexity = NLM_SGMII_DUPLEX_HALF;
			duplexity = "half";
		}

		printf("Port [%d, %d] setup with speed=%s duplex=%s\n",
		    sc->block, sc->port, speed, duplexity);

		nlm_nae_setup_mac(sc->base_addr, sc->block, sc->port, 0, 1, 1,
		    sc->speed, sc->duplexity);
	}
}