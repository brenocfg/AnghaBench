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
 scalar_t__ MGE_READ (struct mge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGE_REG_SMI ; 
 scalar_t__ MGE_SMI_BUSY ; 
 scalar_t__ MGE_SMI_DATA_MASK ; 
 int /*<<< orphan*/  MGE_SMI_DELAY ; 
 int /*<<< orphan*/  MGE_SMI_LOCK () ; 
 int MGE_SMI_MASK ; 
 int MGE_SMI_READ ; 
 scalar_t__ MGE_SMI_READVALID ; 
 int /*<<< orphan*/  MGE_SMI_UNLOCK () ; 
 int /*<<< orphan*/  MGE_SMI_WRITE_DELAY ; 
 scalar_t__ MGE_SMI_WRITE_RETRIES ; 
 int /*<<< orphan*/  MGE_WRITE (struct mge_softc*,int /*<<< orphan*/ ,int) ; 
 struct mge_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static uint32_t
mv_read_ge_smi(device_t dev, int phy, int reg)
{
	uint32_t timeout;
	uint32_t ret;
	struct mge_softc *sc;

	sc = device_get_softc(dev);
	KASSERT(sc != NULL, ("NULL softc ptr!"));
	timeout = MGE_SMI_WRITE_RETRIES;

	MGE_SMI_LOCK();
	while (--timeout &&
	    (MGE_READ(sc, MGE_REG_SMI) & MGE_SMI_BUSY))
		MGE_DELAY(MGE_SMI_WRITE_DELAY);

	if (timeout == 0) {
		device_printf(dev, "SMI write timeout.\n");
		ret = ~0U;
		goto out;
	}

	MGE_WRITE(sc, MGE_REG_SMI, MGE_SMI_MASK &
	    (MGE_SMI_READ | (reg << 21) | (phy << 16)));

	/* Wait till finished. */
	timeout = MGE_SMI_WRITE_RETRIES;
	while (--timeout &&
	    !((MGE_READ(sc, MGE_REG_SMI) & MGE_SMI_READVALID)))
		MGE_DELAY(MGE_SMI_WRITE_DELAY);

	if (timeout == 0) {
		device_printf(dev, "SMI write validation timeout.\n");
		ret = ~0U;
		goto out;
	}

	/* Wait for the data to update in the SMI register */
	MGE_DELAY(MGE_SMI_DELAY);
	ret = MGE_READ(sc, MGE_REG_SMI) & MGE_SMI_DATA_MASK;

out:
	MGE_SMI_UNLOCK();
	return (ret);

}