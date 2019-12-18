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
struct ncr53c9x_softc {int dummy; } ;
struct esp_pci_softc {int dummy; } ;

/* Variables and functions */
 int NCRSTAT_INT ; 
 int /*<<< orphan*/  NCR_STAT ; 
 int READ_ESPREG (struct esp_pci_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
esp_pci_dma_isintr(struct ncr53c9x_softc *sc)
{
	struct esp_pci_softc *esc = (struct esp_pci_softc *)sc;

	return (READ_ESPREG(esc, NCR_STAT) & NCRSTAT_INT) != 0;
}