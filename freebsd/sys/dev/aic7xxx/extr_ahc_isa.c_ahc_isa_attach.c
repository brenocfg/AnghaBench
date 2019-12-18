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
struct resource {int dummy; } ;
struct aic7770_identity {int dummy; } ;
struct ahc_softc {int /*<<< orphan*/  dev_softc; int /*<<< orphan*/  parent_dmat; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  AHC_MAXTRANSFER_SIZE ; 
 int /*<<< orphan*/  AHC_NSEG ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXSIZE_32BIT ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 struct ahc_softc* ahc_alloc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ahc_attach (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_free (struct ahc_softc*) ; 
 struct aic7770_identity* ahc_isa_find_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_set_unit (struct ahc_softc*,int /*<<< orphan*/ ) ; 
 int aic7770_config (struct ahc_softc*,struct aic7770_identity*,int /*<<< orphan*/ ) ; 
 int aic_dma_tag_create (struct ahc_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 char* malloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  rman_get_bushandle (struct resource*) ; 
 int /*<<< orphan*/  rman_get_bustag (struct resource*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ahc_isa_attach(device_t dev)
{
	struct	 aic7770_identity *entry;
	bus_space_tag_t	    tag;
	bus_space_handle_t  bsh;
	struct	  resource *regs;
	struct	  ahc_softc *ahc;
	char	 *name;
	int	  zero;
	int	  error;

	zero = 0;
	regs = bus_alloc_resource_any(dev, SYS_RES_IOPORT, &zero, RF_ACTIVE);
	if (regs == NULL)
		return (ENOMEM);

	tag = rman_get_bustag(regs);
	bsh = rman_get_bushandle(regs);
	entry = ahc_isa_find_device(tag, bsh);
	bus_release_resource(dev, SYS_RES_IOPORT, zero, regs);
	if (entry == NULL)
		return (ENODEV);

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

	/* Allocate a dmatag for our SCB DMA maps */
	error = aic_dma_tag_create(ahc, /*parent*/bus_get_dma_tag(dev),
				   /*alignment*/1, /*boundary*/0,
				   /*lowaddr*/BUS_SPACE_MAXADDR_32BIT,
				   /*highaddr*/BUS_SPACE_MAXADDR,
				   /*filter*/NULL, /*filterarg*/NULL,
				   /*maxsize*/BUS_SPACE_MAXSIZE_32BIT,
				   /*nsegments*/AHC_NSEG,
				   /*maxsegsz*/AHC_MAXTRANSFER_SIZE,
				   /*flags*/0,
				   &ahc->parent_dmat);

	if (error != 0) {
		printf("ahc_isa_attach: Could not allocate DMA tag "
		       "- error %d\n", error);
		ahc_free(ahc);
		return (ENOMEM);
	}
	ahc->dev_softc = dev;
	error = aic7770_config(ahc, entry, /*unused ioport arg*/0);
	if (error != 0) {
		ahc_free(ahc);
		return (error);
	}

	ahc_attach(ahc);
	return (0);
}