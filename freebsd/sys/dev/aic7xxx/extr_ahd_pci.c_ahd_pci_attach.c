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
struct ahd_softc {int flags; int /*<<< orphan*/  dev_softc; int /*<<< orphan*/  parent_dmat; } ;
struct ahd_pci_identity {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int AHD_39BIT_ADDRESSING ; 
 int /*<<< orphan*/  AHD_MAXTRANSFER_SIZE ; 
 int /*<<< orphan*/  AHD_NSEG ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXSIZE_32BIT ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 struct ahd_softc* ahd_alloc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ahd_attach (struct ahd_softc*) ; 
 struct ahd_pci_identity* ahd_find_pci_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_free (struct ahd_softc*) ; 
 int ahd_pci_config (struct ahd_softc*,struct ahd_pci_identity*) ; 
 int /*<<< orphan*/  ahd_set_unit (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_sysctl (struct ahd_softc*) ; 
 int aic_dma_tag_create (struct ahd_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 char* malloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ahd_pci_attach(device_t dev)
{
	struct	 ahd_pci_identity *entry;
	struct	 ahd_softc *ahd;
	char	*name;
	int	 error;

	entry = ahd_find_pci_device(dev);
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
	ahd = ahd_alloc(dev, name);
	if (ahd == NULL)
		return (ENOMEM);

	ahd_set_unit(ahd, device_get_unit(dev));

	/*
	 * Should we bother disabling 39Bit addressing
	 * based on installed memory?
	 */
	if (sizeof(bus_addr_t) > 4)
                ahd->flags |= AHD_39BIT_ADDRESSING;

	/* Allocate a dmatag for our SCB DMA maps */
	error = aic_dma_tag_create(ahd, /*parent*/bus_get_dma_tag(dev),
				   /*alignment*/1, /*boundary*/0,
				   (ahd->flags & AHD_39BIT_ADDRESSING)
				   ? 0x7FFFFFFFFF
				   : BUS_SPACE_MAXADDR_32BIT,
				   /*highaddr*/BUS_SPACE_MAXADDR,
				   /*filter*/NULL, /*filterarg*/NULL,
				   /*maxsize*/BUS_SPACE_MAXSIZE_32BIT,
				   /*nsegments*/AHD_NSEG,
				   /*maxsegsz*/AHD_MAXTRANSFER_SIZE,
				   /*flags*/0,
				   &ahd->parent_dmat);

	if (error != 0) {
		printf("ahd_pci_attach: Could not allocate DMA tag "
		       "- error %d\n", error);
		ahd_free(ahd);
		return (ENOMEM);
	}
	ahd->dev_softc = dev;
	error = ahd_pci_config(ahd, entry);
	if (error != 0) {
		ahd_free(ahd);
		return (error);
	}

	ahd_sysctl(ahd);
	ahd_attach(ahd);
	return (0);
}