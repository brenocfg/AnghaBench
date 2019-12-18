#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct hdac_softc {int num_ss; int /*<<< orphan*/  lock; int /*<<< orphan*/ * chan_dmat; int /*<<< orphan*/  corb_dma; int /*<<< orphan*/  rirb_dma; int /*<<< orphan*/  pos_dma; TYPE_2__* streams; int /*<<< orphan*/  unsolq_task; TYPE_1__* codecs; } ;
struct TYPE_12__ {int /*<<< orphan*/  bdl; } ;
typedef  TYPE_2__ device_t ;
struct TYPE_11__ {int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_HDAC ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int device_delete_child (TYPE_2__,TYPE_2__) ; 
 int device_get_children (TYPE_2__,TYPE_2__**,int*) ; 
 scalar_t__ device_get_ivars (TYPE_2__) ; 
 struct hdac_softc* device_get_softc (TYPE_2__) ; 
 int /*<<< orphan*/  free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdac_dma_free (struct hdac_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hdac_irq_free (struct hdac_softc*) ; 
 int /*<<< orphan*/  hdac_lock (struct hdac_softc*) ; 
 int /*<<< orphan*/  hdac_mem_free (struct hdac_softc*) ; 
 int /*<<< orphan*/  hdac_reset (struct hdac_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdac_unlock (struct hdac_softc*) ; 
 int /*<<< orphan*/  snd_mtxfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_thread ; 

__attribute__((used)) static int
hdac_detach(device_t dev)
{
	struct hdac_softc *sc = device_get_softc(dev);
	device_t *devlist;
	int cad, i, devcount, error;

	if ((error = device_get_children(dev, &devlist, &devcount)) != 0)
		return (error);
	for (i = 0; i < devcount; i++) {
		cad = (intptr_t)device_get_ivars(devlist[i]);
		if ((error = device_delete_child(dev, devlist[i])) != 0) {
			free(devlist, M_TEMP);
			return (error);
		}
		sc->codecs[cad].dev = NULL;
	}
	free(devlist, M_TEMP);

	hdac_lock(sc);
	hdac_reset(sc, 0);
	hdac_unlock(sc);
	taskqueue_drain(taskqueue_thread, &sc->unsolq_task);
	hdac_irq_free(sc);

	for (i = 0; i < sc->num_ss; i++)
		hdac_dma_free(sc, &sc->streams[i].bdl);
	free(sc->streams, M_HDAC);
	hdac_dma_free(sc, &sc->pos_dma);
	hdac_dma_free(sc, &sc->rirb_dma);
	hdac_dma_free(sc, &sc->corb_dma);
	if (sc->chan_dmat != NULL) {
		bus_dma_tag_destroy(sc->chan_dmat);
		sc->chan_dmat = NULL;
	}
	hdac_mem_free(sc);
	snd_mtxfree(sc->lock);
	return (0);
}