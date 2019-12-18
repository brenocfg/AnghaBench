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
struct bxe_softc {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCICFG_GRC_ADDRESS ; 
 int /*<<< orphan*/  PCICFG_GRC_DATA ; 
 int /*<<< orphan*/  pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

uint32_t
bxe_reg_rd_ind(struct bxe_softc *sc,
               uint32_t         addr)
{
    uint32_t val;

    pci_write_config(sc->dev, PCICFG_GRC_ADDRESS, addr, 4);
    val = pci_read_config(sc->dev, PCICFG_GRC_DATA, 4);
    pci_write_config(sc->dev, PCICFG_GRC_ADDRESS, 0, 4);

    return (val);
}