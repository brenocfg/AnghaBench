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
typedef  int /*<<< orphan*/  uint32_t ;
struct smc_softc {int /*<<< orphan*/  smc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BSR ; 
 int BSR_BANK_MASK ; 
 int BUS_SPACE_BARRIER_READ ; 
 int BUS_SPACE_BARRIER_WRITE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MGMT ; 
 int /*<<< orphan*/  SMC_ASSERT_LOCKED (struct smc_softc*) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct smc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smc_barrier (struct smc_softc*,int /*<<< orphan*/ ,int,int) ; 
 int smc_read_2 (struct smc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smc_write_2 (struct smc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
smc_mii_bitbang_write(device_t dev, uint32_t val)
{
	struct smc_softc	*sc;

	sc = device_get_softc(dev);

	SMC_ASSERT_LOCKED(sc);
	KASSERT((smc_read_2(sc, BSR) & BSR_BANK_MASK) == 3,
	    ("%s: smc_mii_bitbang_write called with bank %d (!= 3)",
	    device_get_nameunit(sc->smc_dev),
	    smc_read_2(sc, BSR) & BSR_BANK_MASK));

	smc_write_2(sc, MGMT, val);
	smc_barrier(sc, MGMT, 2,
	    BUS_SPACE_BARRIER_READ | BUS_SPACE_BARRIER_WRITE);
}