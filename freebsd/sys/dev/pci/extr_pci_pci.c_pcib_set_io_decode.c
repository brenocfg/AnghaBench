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
struct pcib_softc {int iobase; int iolimit; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCIR_IOBASEH_1 ; 
 int /*<<< orphan*/  PCIR_IOBASEL_1 ; 
 int /*<<< orphan*/  PCIR_IOLIMITH_1 ; 
 int /*<<< orphan*/  PCIR_IOLIMITL_1 ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
pcib_set_io_decode(struct pcib_softc *sc)
{
	device_t	dev;
	uint32_t	iohi;

	dev = sc->dev;

	iohi = sc->iobase >> 16;
	if (iohi > 0)
		pci_write_config(dev, PCIR_IOBASEH_1, iohi, 2);
	pci_write_config(dev, PCIR_IOBASEL_1, sc->iobase >> 8, 1);

	iohi = sc->iolimit >> 16;
	if (iohi > 0)
		pci_write_config(dev, PCIR_IOLIMITH_1, iohi, 2);
	pci_write_config(dev, PCIR_IOLIMITL_1, sc->iolimit >> 8, 1);
}