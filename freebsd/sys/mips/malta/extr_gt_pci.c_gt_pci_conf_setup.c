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
struct gt_pci_softc {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int
gt_pci_conf_setup(struct gt_pci_softc *sc, int bus, int slot, int func,
    int reg, uint32_t *addr)
{
	*addr = (bus << 16) | (slot << 11) | (func << 8) | reg;

	return (0);
}