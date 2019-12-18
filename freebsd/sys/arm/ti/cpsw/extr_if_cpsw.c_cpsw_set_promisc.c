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
struct cpswp_softc {int /*<<< orphan*/  swsc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPSW_ALE_CONTROL ; 
 int /*<<< orphan*/  CPSW_ALE_CTL_BYPASS ; 
 int /*<<< orphan*/  cpsw_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cpsw_set_promisc(struct cpswp_softc *sc, int set)
{
	uint32_t reg;

	/*
	 * Enabling promiscuous mode requires ALE_BYPASS to be enabled.
	 * That disables the ALE forwarding logic and causes every
	 * packet to be sent only to the host port.  In bypass mode,
	 * the ALE processes host port transmit packets the same as in
	 * normal mode.
	 */
	reg = cpsw_read_4(sc->swsc, CPSW_ALE_CONTROL);
	reg &= ~CPSW_ALE_CTL_BYPASS;
	if (set)
		reg |= CPSW_ALE_CTL_BYPASS;
	cpsw_write_4(sc->swsc, CPSW_ALE_CONTROL, reg);
}