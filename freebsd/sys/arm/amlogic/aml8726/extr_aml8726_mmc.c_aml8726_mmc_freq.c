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
struct aml8726_mmc_softc {int ref_freq; } ;

/* Variables and functions */

__attribute__((used)) static uint32_t
aml8726_mmc_freq(struct aml8726_mmc_softc *sc, uint32_t divisor)
{

	return (sc->ref_freq / ((divisor + 1) * 2));
}