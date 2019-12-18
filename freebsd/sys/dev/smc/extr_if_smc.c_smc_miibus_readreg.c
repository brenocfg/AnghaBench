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
struct smc_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SMC_LOCK (struct smc_softc*) ; 
 int /*<<< orphan*/  SMC_UNLOCK (struct smc_softc*) ; 
 struct smc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int mii_bitbang_readreg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  smc_mii_bitbang_ops ; 
 int /*<<< orphan*/  smc_select_bank (struct smc_softc*,int) ; 

int
smc_miibus_readreg(device_t dev, int phy, int reg)
{
	struct smc_softc	*sc;
	int			val;

	sc = device_get_softc(dev);

	SMC_LOCK(sc);

	smc_select_bank(sc, 3);

	val = mii_bitbang_readreg(dev, &smc_mii_bitbang_ops, phy, reg);

	SMC_UNLOCK(sc);
	return (val);
}