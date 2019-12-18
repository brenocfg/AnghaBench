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
typedef  scalar_t__ uint32_t ;
struct mge_softc {int /*<<< orphan*/  phy_sc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int /*<<< orphan*/ ) ; 
 scalar_t__ MGE_READ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGE_REG_SMI ; 
 scalar_t__ MGE_SMI_DATA_MASK ; 
 int /*<<< orphan*/  MGE_SMI_LOCK () ; 
 int MGE_SMI_MASK ; 
 int MGE_SMI_READ ; 
 scalar_t__ MGE_SMI_READVALID ; 
 int /*<<< orphan*/  MGE_SMI_READ_DELAY ; 
 scalar_t__ MGE_SMI_READ_RETRIES ; 
 int /*<<< orphan*/  MGE_SMI_UNLOCK () ; 
 int /*<<< orphan*/  MGE_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct mge_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
mv_read_ext_phy(device_t dev, int phy, int reg)
{
	uint32_t retries;
	struct mge_softc *sc;
	uint32_t ret;

	sc = device_get_softc(dev);

	MGE_SMI_LOCK();
	MGE_WRITE(sc->phy_sc, MGE_REG_SMI, MGE_SMI_MASK &
	    (MGE_SMI_READ | (reg << 21) | (phy << 16)));

	retries = MGE_SMI_READ_RETRIES;
	while (--retries &&
	    !(MGE_READ(sc->phy_sc, MGE_REG_SMI) & MGE_SMI_READVALID))
		DELAY(MGE_SMI_READ_DELAY);

	if (retries == 0)
		device_printf(dev, "Timeout while reading from PHY\n");

	ret = MGE_READ(sc->phy_sc, MGE_REG_SMI) & MGE_SMI_DATA_MASK;
	MGE_SMI_UNLOCK();

	return (ret);
}