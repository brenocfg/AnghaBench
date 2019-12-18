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
typedef  int /*<<< orphan*/  uint8_t ;
struct cbb_softc {int /*<<< orphan*/ * exca; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXCA_INTR ; 
 int /*<<< orphan*/  exca_putb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cbb_o2micro_power_hack2(struct cbb_softc *sc, uint8_t reg)
{
	exca_putb(&sc->exca[0], EXCA_INTR, reg);
}