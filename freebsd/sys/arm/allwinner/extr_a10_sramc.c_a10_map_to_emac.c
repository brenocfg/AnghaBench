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
typedef  int uint32_t ;
struct a10_sramc_softc {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  SRAM_CTL1_CFG ; 
 struct a10_sramc_softc* a10_sramc_sc ; 
 int sramc_read_4 (struct a10_sramc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sramc_write_4 (struct a10_sramc_softc*,int /*<<< orphan*/ ,int) ; 

int
a10_map_to_emac(void)
{
	struct a10_sramc_softc *sc = a10_sramc_sc;
	uint32_t reg_value;

	if (sc == NULL)
		return (ENXIO);

	/* Map SRAM to EMAC, set bit 2 and 4. */
	reg_value = sramc_read_4(sc, SRAM_CTL1_CFG);
	reg_value |= 0x5 << 2;
	sramc_write_4(sc, SRAM_CTL1_CFG, reg_value);

	return (0);
}