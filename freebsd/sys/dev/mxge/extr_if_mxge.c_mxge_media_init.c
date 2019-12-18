#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* product_code_string; int /*<<< orphan*/  dev; int /*<<< orphan*/  connector; int /*<<< orphan*/  media; } ;
typedef  TYPE_1__ mxge_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  IFM_10G_CX4 ; 
 int /*<<< orphan*/  IFM_AUTO ; 
 int /*<<< orphan*/  MXGE_CX4 ; 
 int /*<<< orphan*/  MXGE_QRF ; 
 int /*<<< orphan*/  MXGE_SFP ; 
 int /*<<< orphan*/  MXGE_XFP ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ifmedia_removeall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mxge_media_set (TYPE_1__*,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static void
mxge_media_init(mxge_softc_t *sc)
{
	char *ptr;
	int i;

	ifmedia_removeall(&sc->media);
	mxge_media_set(sc, IFM_AUTO);

	/*
	 * parse the product code to deterimine the interface type
	 * (CX4, XFP, Quad Ribbon Fiber) by looking at the character
	 * after the 3rd dash in the driver's cached copy of the
	 * EEPROM's product code string.
	 */
	ptr = sc->product_code_string;
	if (ptr == NULL) {
		device_printf(sc->dev, "Missing product code\n");
		return;
	}

	for (i = 0; i < 3; i++, ptr++) {
		ptr = strchr(ptr, '-');
		if (ptr == NULL) {
			device_printf(sc->dev,
				      "only %d dashes in PC?!?\n", i);
			return;
		}
	}
	if (*ptr == 'C' || *(ptr +1) == 'C') {
		/* -C is CX4 */
		sc->connector = MXGE_CX4;
		mxge_media_set(sc, IFM_10G_CX4);
	} else if (*ptr == 'Q') {
		/* -Q is Quad Ribbon Fiber */
		sc->connector = MXGE_QRF;
		device_printf(sc->dev, "Quad Ribbon Fiber Media\n");
		/* FreeBSD has no media type for Quad ribbon fiber */
	} else if (*ptr == 'R') {
		/* -R is XFP */
		sc->connector = MXGE_XFP;
	} else if (*ptr == 'S' || *(ptr +1) == 'S') {
		/* -S or -2S is SFP+ */
		sc->connector = MXGE_SFP;
	} else {
		device_printf(sc->dev, "Unknown media type: %c\n", *ptr);
	}
}