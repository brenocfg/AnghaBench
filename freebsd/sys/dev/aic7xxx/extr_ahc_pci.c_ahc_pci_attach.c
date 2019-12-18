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
struct ahc_softc {int flags; int /*<<< orphan*/  dev_softc; int /*<<< orphan*/  parent_dmat; } ;
struct ahc_pci_identity {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int AHC_39BIT_ADDRESSING ; 
 int /*<<< orphan*/  AHC_MAXTRANSFER_SIZE ; 
 int /*<<< orphan*/  AHC_NSEG ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXSIZE_32BIT ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 struct ahc_softc* ahc_alloc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ahc_attach (struct ahc_softc*) ; 
 struct ahc_pci_identity* ahc_find_pci_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_free (struct ahc_softc*) ; 
 int ahc_pci_config (struct ahc_softc*,struct ahc_pci_identity*) ; 
 int /*<<< orphan*/  ahc_set_unit (struct ahc_softc*,int /*<<< orphan*/ ) ; 
 int aic_dma_tag_create (struct ahc_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 char* malloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ahc_pci_attach(device_t dev)
{
	struct	 ahc_pci_identity *entry;
	struct	 ahc_softc *ahc;
	char	*name;
	int	 error;

	entry = ahc_find_pci_device(dev);
	if (entry == NULL)
		return (ENXIO);

	/*
	 * Allocate a softc for this card and
	 * set it up for attachment by our
	 * common detect routine.
	 */
	name = malloc(strlen(device_get_nameunit(dev)) + 1, M_DEVBUF, M_NOWAIT);
	if (name == NULL)
		return (ENOMEM);
	strcpy(name, device_get_nameunit(dev));
	ahc = ahc_alloc(dev, name);
	if (ahc == NULL)
		return (ENOMEM);

	ahc_set_unit(ahc, device_get_unit(dev));

	/*
	 * Should we bother disabling 39Bit addressing
	 * based on installed memory?
	 */
	if (sizeof(bus_addr_t) > 4)
                ahc->flags |= AHC_39BIT_ADDRESSING;

	/* Allocate a dmatag for our SCB DMA maps */
	error = aic_dma_tag_create(ahc, /*parent*/bus_get_dma_tag(dev),
				   /*alignment*/1, /*boundary*/0,
				   (ahc->flags & AHC_39BIT_ADDRESSING)
				   ? 0x7FFFFFFFFFLL
				   : BUS_SPACE_MAXADDR_32BIT,
				   /*highaddr*/BUS_SPACE_MAXADDR,
				   /*filter*/NULL, /*filterarg*/NULL,
				   /*maxsize*/BUS_SPACE_MAXSIZE_32BIT,
				   /*nsegments*/AHC_NSEG,
				   /*maxsegsz*/AHC_MAXTRANSFER_SIZE,
				   /*flags*/0,
				   &ahc->parent_dmat);

	if (error != 0) {
		printf("ahc_pci_attach: Could not allocate DMA tag "
		       "- error %d\n", error);
		ahc_free(ahc);
		return (ENOMEM);
	}
	ahc->dev_softc = dev;
	error = ahc_pci_config(ahc, entry);
	if (error != 0) {
		ahc_free(ahc);
		return (error);
	}

	ahc_attach(ahc);
	return (0);
}