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
struct mii_data {int /*<<< orphan*/  mii_media_active; } ;
struct mgb_softc {int /*<<< orphan*/  baudrate; int /*<<< orphan*/  link_state; int /*<<< orphan*/  ctx; int /*<<< orphan*/  miibus; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 struct mgb_softc* iflib_get_softc (struct mii_data*) ; 
 int /*<<< orphan*/  iflib_link_state_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_baudrate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mgb_miibus_statchg(device_t dev)
{
	struct mgb_softc *sc;
	struct mii_data *miid;

	sc = iflib_get_softc(device_get_softc(dev));
	miid = device_get_softc(sc->miibus);
	/* Update baudrate in iflib */
	sc->baudrate = ifmedia_baudrate(miid->mii_media_active);
	iflib_link_state_change(sc->ctx, sc->link_state, sc->baudrate);
}