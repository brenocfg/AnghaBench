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
typedef  int /*<<< orphan*/  uint64_t ;
struct pci_xhci_softc {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static uint64_t
pci_xhci_dbregs_read(struct pci_xhci_softc *sc, uint64_t offset)
{

	/* read doorbell always returns 0 */
	return (0);
}