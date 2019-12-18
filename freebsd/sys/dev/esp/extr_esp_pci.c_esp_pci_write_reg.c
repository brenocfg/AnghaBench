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
 int /*<<< orphan*/  WRITE_ESPREG (struct esp_pci_softc*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
esp_pci_write_reg(struct ncr53c9x_softc *sc, int reg, uint8_t v)
{
	struct esp_pci_softc *esc = (struct esp_pci_softc *)sc;

	WRITE_ESPREG(esc, reg, v);
}