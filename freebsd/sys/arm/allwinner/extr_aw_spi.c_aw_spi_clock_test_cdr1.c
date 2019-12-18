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
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct aw_spi_softc {int mod_freq; } ;

/* Variables and functions */
 int AW_SPI_CCR_CDR1_MASK ; 
 int AW_SPI_CCR_CDR1_SHIFT ; 

__attribute__((used)) static uint64_t
aw_spi_clock_test_cdr1(struct aw_spi_softc *sc, uint64_t clock, uint32_t *ccr)
{
	uint64_t cur, best = 0;
	int i, max, best_div;

	max = AW_SPI_CCR_CDR1_MASK >> AW_SPI_CCR_CDR1_SHIFT;
	for (i = 0; i < max; i++) {
		cur = sc->mod_freq / (1 << i);
		if ((clock - cur) < (clock - best)) {
			best = cur;
			best_div = i;
		}
	}

	*ccr = (best_div << AW_SPI_CCR_CDR1_SHIFT);
	return (best);
}