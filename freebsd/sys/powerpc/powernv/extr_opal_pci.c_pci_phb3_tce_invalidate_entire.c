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
struct opalpci_softc {int /*<<< orphan*/  r_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHB3_TCE_KILL_INVAL_ALL ; 
 int /*<<< orphan*/  bus_write_8 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static void
pci_phb3_tce_invalidate_entire(struct opalpci_softc *sc)
{

	mb();
	bus_write_8(sc->r_reg, 0x210, PHB3_TCE_KILL_INVAL_ALL);
	mb();
}