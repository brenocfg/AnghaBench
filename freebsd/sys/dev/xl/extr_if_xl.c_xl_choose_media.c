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
struct xl_softc {int xl_xcvr; int /*<<< orphan*/  xl_dev; int /*<<< orphan*/  xl_media; int /*<<< orphan*/  xl_type; } ;

/* Variables and functions */
 int IFM_100_FX ; 
 int IFM_10_2 ; 
 int IFM_10_5 ; 
 int IFM_10_FL ; 
 int IFM_10_T ; 
 int IFM_ETHER ; 
 int /*<<< orphan*/  XL_LOCK (struct xl_softc*) ; 
 int /*<<< orphan*/  XL_MEDIAOPT_10FL ; 
 int /*<<< orphan*/  XL_TYPE_905B ; 
 int /*<<< orphan*/  XL_UNLOCK (struct xl_softc*) ; 
#define  XL_XCVR_100BFX 134 
#define  XL_XCVR_100BTX 133 
#define  XL_XCVR_10BT 132 
#define  XL_XCVR_AUI 131 
#define  XL_XCVR_AUTO 130 
#define  XL_XCVR_COAX 129 
#define  XL_XCVR_MII 128 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  xl_setmode (struct xl_softc*,int) ; 

__attribute__((used)) static void
xl_choose_media(struct xl_softc *sc, int *media)
{

	XL_LOCK(sc);

	switch (sc->xl_xcvr) {
	case XL_XCVR_10BT:
		*media = IFM_ETHER|IFM_10_T;
		xl_setmode(sc, *media);
		break;
	case XL_XCVR_AUI:
		if (sc->xl_type == XL_TYPE_905B &&
		    sc->xl_media == XL_MEDIAOPT_10FL) {
			*media = IFM_ETHER|IFM_10_FL;
			xl_setmode(sc, *media);
		} else {
			*media = IFM_ETHER|IFM_10_5;
			xl_setmode(sc, *media);
		}
		break;
	case XL_XCVR_COAX:
		*media = IFM_ETHER|IFM_10_2;
		xl_setmode(sc, *media);
		break;
	case XL_XCVR_AUTO:
	case XL_XCVR_100BTX:
	case XL_XCVR_MII:
		/* Chosen by miibus */
		break;
	case XL_XCVR_100BFX:
		*media = IFM_ETHER|IFM_100_FX;
		break;
	default:
		device_printf(sc->xl_dev, "unknown XCVR type: %d\n",
		    sc->xl_xcvr);
		/*
		 * This will probably be wrong, but it prevents
		 * the ifmedia code from panicking.
		 */
		*media = IFM_ETHER|IFM_10_T;
		break;
	}

	XL_UNLOCK(sc);
}