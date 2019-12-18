#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct sndcard_func {int /*<<< orphan*/  func; TYPE_1__* varinfo; } ;
typedef  TYPE_2__* sc_p ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_16__ {int /*<<< orphan*/ * io; void* io_rid; int /*<<< orphan*/ * mem; void* mem_rid; int /*<<< orphan*/ * irq; void* irq_rid; } ;
typedef  TYPE_3__ csa_res ;
struct TYPE_14__ {TYPE_10__* card; } ;
struct TYPE_15__ {int /*<<< orphan*/  ih; void* midi; TYPE_1__ binfo; void* pcm; TYPE_10__* card; TYPE_3__ res; int /*<<< orphan*/  dev; } ;
struct TYPE_13__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BA0_HICR ; 
 int /*<<< orphan*/  BA0_HISR ; 
 int ENOMEM ; 
 int ENXIO ; 
 int HICR_CHGM ; 
 int HICR_IEV ; 
 int HISR_INTENA ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 void* PCIR_BAR (int) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SCF_MIDI ; 
 int /*<<< orphan*/  SCF_PCM ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,int) ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 scalar_t__ csa_downloadimage (TYPE_3__*) ; 
 TYPE_10__* csa_findsubcard (int /*<<< orphan*/ ) ; 
 scalar_t__ csa_initialize (TYPE_2__*) ; 
 int /*<<< orphan*/  csa_intr ; 
 int csa_readio (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csa_resetdsp (TYPE_3__*) ; 
 int /*<<< orphan*/  csa_writeio (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 void* device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_2__* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_ivars (void*,struct sndcard_func*) ; 
 struct sndcard_func* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ snd_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
csa_attach(device_t dev)
{
	sc_p scp;
	csa_res *resp;
	struct sndcard_func *func;
	int error = ENXIO;

	scp = device_get_softc(dev);

	/* Fill in the softc. */
	bzero(scp, sizeof(*scp));
	scp->dev = dev;

	pci_enable_busmaster(dev);

	/* Allocate the resources. */
	resp = &scp->res;
	scp->card = csa_findsubcard(dev);
	scp->binfo.card = scp->card;
	printf("csa: card is %s\n", scp->card->name);
	resp->io_rid = PCIR_BAR(0);
	resp->io = bus_alloc_resource_any(dev, SYS_RES_MEMORY, 
		&resp->io_rid, RF_ACTIVE);
	if (resp->io == NULL)
		return (ENXIO);
	resp->mem_rid = PCIR_BAR(1);
	resp->mem = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
		&resp->mem_rid, RF_ACTIVE);
	if (resp->mem == NULL)
		goto err_io;
	resp->irq_rid = 0;
	resp->irq = bus_alloc_resource_any(dev, SYS_RES_IRQ,
		&resp->irq_rid, RF_ACTIVE | RF_SHAREABLE);
	if (resp->irq == NULL)
		goto err_mem;

	/* Enable interrupt. */
	if (snd_setup_intr(dev, resp->irq, 0, csa_intr, scp, &scp->ih))
		goto err_intr;
#if 0
	if ((csa_readio(resp, BA0_HISR) & HISR_INTENA) == 0)
		csa_writeio(resp, BA0_HICR, HICR_IEV | HICR_CHGM);
#endif

	/* Initialize the chip. */
	if (csa_initialize(scp))
		goto err_teardown;

	/* Reset the Processor. */
	csa_resetdsp(resp);

	/* Download the Processor Image to the processor. */
	if (csa_downloadimage(resp))
		goto err_teardown;

	/* Attach the children. */

	/* PCM Audio */
	func = malloc(sizeof(struct sndcard_func), M_DEVBUF, M_NOWAIT | M_ZERO);
	if (func == NULL) {
		error = ENOMEM;
		goto err_teardown;
	}
	func->varinfo = &scp->binfo;
	func->func = SCF_PCM;
	scp->pcm = device_add_child(dev, "pcm", -1);
	device_set_ivars(scp->pcm, func);

	/* Midi Interface */
	func = malloc(sizeof(struct sndcard_func), M_DEVBUF, M_NOWAIT | M_ZERO);
	if (func == NULL) {
		error = ENOMEM;
		goto err_teardown;
	}
	func->varinfo = &scp->binfo;
	func->func = SCF_MIDI;
	scp->midi = device_add_child(dev, "midi", -1);
	device_set_ivars(scp->midi, func);

	bus_generic_attach(dev);

	return (0);

err_teardown:
	bus_teardown_intr(dev, resp->irq, scp->ih);
err_intr:
	bus_release_resource(dev, SYS_RES_IRQ, resp->irq_rid, resp->irq);
err_mem:
	bus_release_resource(dev, SYS_RES_MEMORY, resp->mem_rid, resp->mem);
err_io:
	bus_release_resource(dev, SYS_RES_MEMORY, resp->io_rid, resp->io);
	return (error);
}