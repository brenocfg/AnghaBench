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
struct ncr53c9x_softc {int dummy; } ;
struct esp_pci_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ESPREG (struct esp_pci_softc*,int) ; 

__attribute__((used)) static uint8_t
esp_pci_read_reg(struct ncr53c9x_softc *sc, int reg)
{
	struct esp_pci_softc *esc = (struct esp_pci_softc *)sc;

	return (READ_ESPREG(esc, reg));
}