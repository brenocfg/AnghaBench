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
struct mii_data {int dummy; } ;
struct mgb_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  miibus; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_CLEAR_REG (struct mgb_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_UPDATE_REG (struct mgb_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MGB_RFE_ALLOW_BROADCAST ; 
 int /*<<< orphan*/  MGB_RFE_ALLOW_PERFECT_FILTER ; 
 int MGB_RFE_ALLOW_UNICAST ; 
 int /*<<< orphan*/  MGB_RFE_CTL ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 struct mgb_softc* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgb_dma_init (struct mgb_softc*) ; 
 int mii_mediachg (struct mii_data*) ; 

__attribute__((used)) static void
mgb_init(if_ctx_t ctx)
{
	struct mgb_softc *sc;
	struct mii_data *miid;
	int error;

	sc = iflib_get_softc(ctx);
	miid = device_get_softc(sc->miibus);
	device_printf(sc->dev, "running init ...\n");

	mgb_dma_init(sc);

	/* XXX: Turn off perfect filtering, turn on (broad|multi|uni)cast rx */
	CSR_CLEAR_REG(sc, MGB_RFE_CTL, MGB_RFE_ALLOW_PERFECT_FILTER);
	CSR_UPDATE_REG(sc, MGB_RFE_CTL,
	    MGB_RFE_ALLOW_BROADCAST |
	    MGB_RFE_ALLOW_UNICAST |
	    MGB_RFE_ALLOW_UNICAST);

	error = mii_mediachg(miid);
	KASSERT(!error, ("mii_mediachg returned: %d", error));
}