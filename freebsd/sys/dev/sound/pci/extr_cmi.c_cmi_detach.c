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
struct sc_info {int /*<<< orphan*/  lock; scalar_t__ mpu_reg; int /*<<< orphan*/  mpu_regid; scalar_t__ reg; int /*<<< orphan*/  regid; scalar_t__ mpu; scalar_t__ irq; int /*<<< orphan*/  irqid; int /*<<< orphan*/  ih; int /*<<< orphan*/  parent_dmat; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmi_power (struct sc_info*,int) ; 
 int /*<<< orphan*/  cmi_uninit (struct sc_info*) ; 
 int /*<<< orphan*/  free (struct sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpu401_uninit (scalar_t__) ; 
 struct sc_info* pcm_getdevinfo (int /*<<< orphan*/ ) ; 
 int pcm_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cmi_detach(device_t dev)
{
	struct sc_info *sc;
	int r;

	r = pcm_unregister(dev);
	if (r) return r;

	sc = pcm_getdevinfo(dev);
	cmi_uninit(sc);
	cmi_power(sc, 3);

	bus_dma_tag_destroy(sc->parent_dmat);
	bus_teardown_intr(dev, sc->irq, sc->ih);
	bus_release_resource(dev, SYS_RES_IRQ, sc->irqid, sc->irq);
	if(sc->mpu)
		mpu401_uninit(sc->mpu);
	bus_release_resource(dev, SYS_RES_IOPORT, sc->regid, sc->reg);
	if (sc->mpu_reg)
	    bus_release_resource(dev, SYS_RES_IOPORT, sc->mpu_regid, sc->mpu_reg);

	snd_mtxfree(sc->lock);
	free(sc, M_DEVBUF);

	return 0;
}