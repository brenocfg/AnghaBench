#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sc_info {int adcn; int dacn; int /*<<< orphan*/  lock; int /*<<< orphan*/  mt; int /*<<< orphan*/  mtid; int /*<<< orphan*/  ds; int /*<<< orphan*/  dsid; int /*<<< orphan*/  ddma; int /*<<< orphan*/  ddmaid; int /*<<< orphan*/  cs; int /*<<< orphan*/  csid; int /*<<< orphan*/  irq; int /*<<< orphan*/  irqid; int /*<<< orphan*/  ih; int /*<<< orphan*/  dmat; TYPE_2__* cfg; int /*<<< orphan*/ * dac; int /*<<< orphan*/ * adc; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {TYPE_1__* codec; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* destroy ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  M_ENVY24 ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  envy24_cfgfree (TYPE_2__*) ; 
 int /*<<< orphan*/  envy24_dmafree (struct sc_info*) ; 
 int /*<<< orphan*/  free (struct sc_info*,int /*<<< orphan*/ ) ; 
 struct sc_info* pcm_getdevinfo (int /*<<< orphan*/ ) ; 
 int pcm_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
envy24_pci_detach(device_t dev)
{
	struct sc_info *sc;
	int r;
	int i;

#if(0)
	device_printf(dev, "envy24_pci_detach()\n");
#endif
	sc = pcm_getdevinfo(dev);
	if (sc == NULL)
		return 0;
	r = pcm_unregister(dev);
	if (r)
		return r;

	envy24_dmafree(sc);
	if (sc->cfg->codec->destroy != NULL) {
		for (i = 0; i < sc->adcn; i++)
			sc->cfg->codec->destroy(sc->adc[i]);
		for (i = 0; i < sc->dacn; i++)
			sc->cfg->codec->destroy(sc->dac[i]);
	}
	envy24_cfgfree(sc->cfg);
	bus_dma_tag_destroy(sc->dmat);
	bus_teardown_intr(dev, sc->irq, sc->ih);
	bus_release_resource(dev, SYS_RES_IRQ, sc->irqid, sc->irq);
	bus_release_resource(dev, SYS_RES_IOPORT, sc->csid, sc->cs);
	bus_release_resource(dev, SYS_RES_IOPORT, sc->ddmaid, sc->ddma);
	bus_release_resource(dev, SYS_RES_IOPORT, sc->dsid, sc->ds);
	bus_release_resource(dev, SYS_RES_IOPORT, sc->mtid, sc->mt);
	snd_mtxfree(sc->lock);
	free(sc, M_ENVY24);
	return 0;
}