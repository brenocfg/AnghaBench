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
struct grackle_softc {int /*<<< orphan*/  sc_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  out32rb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
grackle_disable_config(struct grackle_softc *sc)
{
	/*
	 * Clear the GRACKLE_CFG_ENABLE bit to prevent stray
	 * accesses from causing config cycles
	 */
	out32rb(sc->sc_addr, 0);
}