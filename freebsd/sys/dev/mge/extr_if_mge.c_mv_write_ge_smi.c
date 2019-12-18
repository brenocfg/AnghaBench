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
struct mge_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MGE_DELAY (int /*<<< orphan*/ ) ; 
 int MGE_READ (struct mge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGE_REG_SMI ; 
 int MGE_SMI_BUSY ; 
 scalar_t__ MGE_SMI_DATA_MASK ; 
 int /*<<< orphan*/  MGE_SMI_LOCK () ; 
 int MGE_SMI_MASK ; 
 int /*<<< orphan*/  MGE_SMI_READ_DELAY ; 
 scalar_t__ MGE_SMI_READ_RETRIES ; 
 int /*<<< orphan*/  MGE_SMI_UNLOCK () ; 
 int MGE_SMI_WRITE ; 
 int /*<<< orphan*/  MGE_WRITE (struct mge_softc*,int /*<<< orphan*/ ,int) ; 
 struct mge_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
mv_write_ge_smi(device_t dev, int phy, int reg, uint32_t value)
{
	uint32_t timeout;
	struct mge_softc *sc;

	sc = device_get_softc(dev);
	KASSERT(sc != NULL, ("NULL softc ptr!"));

	MGE_SMI_LOCK();
	timeout = MGE_SMI_READ_RETRIES;
	while (--timeout &&
	    (MGE_READ(sc, MGE_REG_SMI) & MGE_SMI_BUSY))
		MGE_DELAY(MGE_SMI_READ_DELAY);

	if (timeout == 0) {
		device_printf(dev, "SMI read timeout.\n");
		goto out;
	}

	MGE_WRITE(sc, MGE_REG_SMI, MGE_SMI_MASK &
	    (MGE_SMI_WRITE | (reg << 21) | (phy << 16) |
	    (value & MGE_SMI_DATA_MASK)));

out:
	MGE_SMI_UNLOCK();
}