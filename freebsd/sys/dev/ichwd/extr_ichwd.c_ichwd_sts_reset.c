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
struct ichwd_softc {int tco_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCO1_STS ; 
 int /*<<< orphan*/  TCO2_STS ; 
 int /*<<< orphan*/  TCO_BOOT_STS ; 
 int /*<<< orphan*/  TCO_SECOND_TO_STS ; 
 int /*<<< orphan*/  TCO_TIMEOUT ; 
 int /*<<< orphan*/  ichwd_write_tco_2 (struct ichwd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
ichwd_sts_reset(struct ichwd_softc *sc)
{
	/*
	 * The watchdog status bits are set to 1 by the hardware to
	 * indicate various conditions.  They can be cleared by software
	 * by writing a 1, not a 0.
	 */
	ichwd_write_tco_2(sc, TCO1_STS, TCO_TIMEOUT);
	/*
	 * According to Intel's docs, clearing SECOND_TO_STS and BOOT_STS must
	 * be done in two separate operations.
	 */
	ichwd_write_tco_2(sc, TCO2_STS, TCO_SECOND_TO_STS);
	if (sc->tco_version < 4)
		ichwd_write_tco_2(sc, TCO2_STS, TCO_BOOT_STS);
}