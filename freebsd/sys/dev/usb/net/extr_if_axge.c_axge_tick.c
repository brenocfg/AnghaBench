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
struct usb_ether {int dummy; } ;
struct mii_data {int dummy; } ;
struct axge_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXGE_LOCK_ASSERT (struct axge_softc*,int /*<<< orphan*/ ) ; 
 struct mii_data* GET_MII (struct axge_softc*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  mii_tick (struct mii_data*) ; 
 struct axge_softc* uether_getsc (struct usb_ether*) ; 

__attribute__((used)) static void
axge_tick(struct usb_ether *ue)
{
	struct axge_softc *sc;
	struct mii_data *mii;

	sc = uether_getsc(ue);
	mii = GET_MII(sc);
	AXGE_LOCK_ASSERT(sc, MA_OWNED);

	mii_tick(mii);
}