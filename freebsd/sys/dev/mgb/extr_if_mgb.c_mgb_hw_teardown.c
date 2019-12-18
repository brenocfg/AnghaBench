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
struct mgb_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_CLEAR_REG (struct mgb_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_REG (struct mgb_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGB_MAC_DSBL ; 
 int /*<<< orphan*/  MGB_MAC_ENBL ; 
 int /*<<< orphan*/  MGB_MAC_RX ; 
 int /*<<< orphan*/  MGB_MAC_TX ; 
 int mgb_wait_for_bits (struct mgb_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mgb_hw_teardown(struct mgb_softc *sc)
{
	int err = 0;

	/* Stop MAC */
	CSR_CLEAR_REG(sc, MGB_MAC_RX, MGB_MAC_ENBL);
	CSR_WRITE_REG(sc, MGB_MAC_TX, MGB_MAC_ENBL);
	if ((err = mgb_wait_for_bits(sc, MGB_MAC_RX, MGB_MAC_DSBL, 0)))
		return (err);
	if ((err = mgb_wait_for_bits(sc, MGB_MAC_TX, MGB_MAC_DSBL, 0)))
		return (err);
	return (err);
}