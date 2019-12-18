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
struct mmc_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_LOCK_DESTROY (struct mmc_softc*) ; 
 struct mmc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int mmc_delete_cards (struct mmc_softc*,int) ; 
 int /*<<< orphan*/  mmc_power_down (struct mmc_softc*) ; 

__attribute__((used)) static int
mmc_detach(device_t dev)
{
	struct mmc_softc *sc = device_get_softc(dev);
	int err;

	err = mmc_delete_cards(sc, true);
	if (err != 0)
		return (err);
	mmc_power_down(sc);
	MMC_LOCK_DESTROY(sc);

	return (0);
}