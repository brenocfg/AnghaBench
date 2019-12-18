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
struct ifnet {int dummy; } ;
struct bce_softc {int bce_flags; struct ifnet* bce_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCE_LOCK_ASSERT (struct bce_softc*) ; 
 int BCE_MFW_ENABLE_FLAG ; 
 int /*<<< orphan*/  BCE_MISC_ENABLE_DEFAULT ; 
 int /*<<< orphan*/  BCE_MISC_ENABLE_SET_BITS ; 
 int /*<<< orphan*/  BCE_VERBOSE_RESET ; 
 int /*<<< orphan*/  BCE_VERBOSE_SPECIAL ; 
 int /*<<< orphan*/  DBENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBEXIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBPRINT (struct bce_softc*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  REG_RD (struct bce_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bce_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bce_ifmedia_upd_locked (struct ifnet*) ; 

__attribute__((used)) static void
bce_mgmt_init_locked(struct bce_softc *sc)
{
	struct ifnet *ifp;

	DBENTER(BCE_VERBOSE_RESET);

	BCE_LOCK_ASSERT(sc);

	/* Bail out if management firmware is not running. */
	if (!(sc->bce_flags & BCE_MFW_ENABLE_FLAG)) {
		DBPRINT(sc, BCE_VERBOSE_SPECIAL,
		    "No management firmware running...\n");
		goto bce_mgmt_init_locked_exit;
	}

	ifp = sc->bce_ifp;

	/* Enable all critical blocks in the MAC. */
	REG_WR(sc, BCE_MISC_ENABLE_SET_BITS, BCE_MISC_ENABLE_DEFAULT);
	REG_RD(sc, BCE_MISC_ENABLE_SET_BITS);
	DELAY(20);

	bce_ifmedia_upd_locked(ifp);

bce_mgmt_init_locked_exit:
	DBEXIT(BCE_VERBOSE_RESET);
}