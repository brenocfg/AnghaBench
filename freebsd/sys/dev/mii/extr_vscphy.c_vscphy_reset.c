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
struct vscphy_softc {int dummy; } ;
struct mii_softc {int mii_mpd_model; } ;

/* Variables and functions */
#define  MII_MODEL_xxVITESSE_VSC8501 128 
 int /*<<< orphan*/  mii_phy_reset (struct mii_softc*) ; 
 int /*<<< orphan*/  vsc8501_reset (struct vscphy_softc*) ; 

__attribute__((used)) static void
vscphy_reset(struct mii_softc *sc)
{
	struct vscphy_softc *vsc = (struct vscphy_softc *)sc;

	switch (sc->mii_mpd_model) {
	case MII_MODEL_xxVITESSE_VSC8501:
		vsc8501_reset(vsc);
		break;
	default:
		mii_phy_reset(sc);
		break;
	}
}