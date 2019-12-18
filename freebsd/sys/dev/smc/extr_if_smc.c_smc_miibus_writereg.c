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
 int /*<<< orphan*/  mii_bitbang_writereg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  smc_mii_bitbang_ops ; 
 int /*<<< orphan*/  smc_select_bank (struct smc_softc*,int) ; 

int
smc_miibus_writereg(device_t dev, int phy, int reg, int data)
{
	struct smc_softc	*sc;

	sc = device_get_softc(dev);

	SMC_LOCK(sc);

	smc_select_bank(sc, 3);

	mii_bitbang_writereg(dev, &smc_mii_bitbang_ops, phy, reg, data);

	SMC_UNLOCK(sc);
	return (0);
}