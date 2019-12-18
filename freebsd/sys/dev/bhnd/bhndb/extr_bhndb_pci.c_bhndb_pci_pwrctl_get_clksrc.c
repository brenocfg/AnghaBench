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
struct bhndb_pci_softc {int /*<<< orphan*/  parent; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ bhnd_clock ;
typedef  int /*<<< orphan*/  bhnd_clksrc ;

/* Variables and functions */
 int /*<<< orphan*/  BHNDB_PCI_GPIO_OUT ; 
 int BHNDB_PCI_GPIO_SCS ; 
 int /*<<< orphan*/  BHND_CLKSRC_PCI ; 
 int /*<<< orphan*/  BHND_CLKSRC_UNKNOWN ; 
 int /*<<< orphan*/  BHND_CLKSRC_XTAL ; 
 scalar_t__ BHND_CLOCK_ILP ; 
 scalar_t__ bhndb_is_pcie_attached (int /*<<< orphan*/ ) ; 
 struct bhndb_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bhnd_clksrc
bhndb_pci_pwrctl_get_clksrc(device_t dev, device_t child,
	bhnd_clock clock)
{
	struct bhndb_pci_softc	*sc;
	uint32_t		 gpio_out;

	sc = device_get_softc(dev);

	/* Only supported on PCI devices */
	if (bhndb_is_pcie_attached(sc->dev))
		return (BHND_CLKSRC_UNKNOWN);

	/* Only ILP is supported */
	if (clock != BHND_CLOCK_ILP)
		return (BHND_CLKSRC_UNKNOWN);

	gpio_out = pci_read_config(sc->parent, BHNDB_PCI_GPIO_OUT, 4);
	if (gpio_out & BHNDB_PCI_GPIO_SCS)
		return (BHND_CLKSRC_PCI);
	else
		return (BHND_CLKSRC_XTAL);
}