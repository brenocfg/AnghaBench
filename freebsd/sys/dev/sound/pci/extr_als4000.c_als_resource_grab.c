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
struct sc_info {int /*<<< orphan*/  parent_dmat; int /*<<< orphan*/  bufsz; int /*<<< orphan*/  ih; int /*<<< orphan*/ * irq; int /*<<< orphan*/  irqid; int /*<<< orphan*/ * reg; int /*<<< orphan*/  sh; int /*<<< orphan*/  st; int /*<<< orphan*/  regid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALS_DEFAULT_BUFSZ ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_24BIT ; 
 int ENXIO ; 
 int /*<<< orphan*/  INTR_MPSAFE ; 
 int /*<<< orphan*/  PCIR_BAR (int /*<<< orphan*/ ) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  als_intr ; 
 int /*<<< orphan*/  als_resource_free (int /*<<< orphan*/ ,struct sc_info*) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pcm_getbuffersize (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 scalar_t__ snd_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sc_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
als_resource_grab(device_t dev, struct sc_info *sc)
{
	sc->regid = PCIR_BAR(0);
	sc->reg = bus_alloc_resource_any(dev, SYS_RES_IOPORT, &sc->regid,
					 RF_ACTIVE);
	if (sc->reg == NULL) {
		device_printf(dev, "unable to allocate register space\n");
		goto bad;
	}
	sc->st = rman_get_bustag(sc->reg);
	sc->sh = rman_get_bushandle(sc->reg);

	sc->irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &sc->irqid,
					 RF_ACTIVE | RF_SHAREABLE);
	if (sc->irq == NULL) {
		device_printf(dev, "unable to allocate interrupt\n");
		goto bad;
	}

	if (snd_setup_intr(dev, sc->irq, INTR_MPSAFE, als_intr,
			   sc, &sc->ih)) {
		device_printf(dev, "unable to setup interrupt\n");
		goto bad;
	}

	sc->bufsz = pcm_getbuffersize(dev, 4096, ALS_DEFAULT_BUFSZ, 65536);

	if (bus_dma_tag_create(/*parent*/bus_get_dma_tag(dev),
			       /*alignment*/2, /*boundary*/0,
			       /*lowaddr*/BUS_SPACE_MAXADDR_24BIT,
			       /*highaddr*/BUS_SPACE_MAXADDR,
			       /*filter*/NULL, /*filterarg*/NULL,
			       /*maxsize*/sc->bufsz,
			       /*nsegments*/1, /*maxsegz*/0x3ffff,
			       /*flags*/0, /*lockfunc*/NULL,
			       /*lockarg*/NULL, &sc->parent_dmat) != 0) {
		device_printf(dev, "unable to create dma tag\n");
		goto bad;
	}
	return 0;
 bad:
	als_resource_free(dev, sc);
	return ENXIO;
}