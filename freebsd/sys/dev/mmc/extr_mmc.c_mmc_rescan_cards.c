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
struct mmc_softc {int child_count; int /*<<< orphan*/ * child_list; int /*<<< orphan*/  dev; } ;
struct mmc_ivars {int /*<<< orphan*/  rca; } ;

/* Variables and functions */
 scalar_t__ MMC_ERR_NONE ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 scalar_t__ bootverbose ; 
 int device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mmc_ivars* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct mmc_ivars*,int /*<<< orphan*/ ) ; 
 scalar_t__ mmc_debug ; 
 scalar_t__ mmc_select_card (struct mmc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_update_child_list (struct mmc_softc*) ; 

__attribute__((used)) static void
mmc_rescan_cards(struct mmc_softc *sc)
{
	struct mmc_ivars *ivar;
	int err, i, j;

	for (i = j = 0; i < sc->child_count; i++) {
		ivar = device_get_ivars(sc->child_list[i]);
		if (mmc_select_card(sc, ivar->rca) != MMC_ERR_NONE) {
			if (bootverbose || mmc_debug)
				device_printf(sc->dev,
				    "Card at relative address %d lost\n",
				    ivar->rca);
			err = device_delete_child(sc->dev, sc->child_list[i]);
			if (err != 0) {
				j++;
				continue;
			}
			free(ivar, M_DEVBUF);
		} else
			j++;
	}
	if (sc->child_count == j)
		goto out;
	sc->child_count = j;
	mmc_update_child_list(sc);
out:
	(void)mmc_select_card(sc, 0);
}