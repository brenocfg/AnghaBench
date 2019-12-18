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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  void msg_set_power_state ;
struct bcm_mbox_softc {int /*<<< orphan*/  property_chan_lock; } ;
struct bcm2835_mbox_hdr {int dummy; } ;
typedef  int /*<<< orphan*/ * device_t ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;
typedef  scalar_t__ bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_MBOX_CHAN_PROP ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  MBOX_READ (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MBOX_WRITE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bcm2835_mbox_err (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,struct bcm2835_mbox_hdr*,size_t) ; 
 void* bcm2835_mbox_init_dma (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devclass_find (char*) ; 
 int /*<<< orphan*/ * devclass_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bcm_mbox_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

int
bcm2835_mbox_property(void *msg, size_t msg_size)
{
	struct bcm_mbox_softc *sc;
	struct msg_set_power_state *buf;
	bus_dma_tag_t msg_tag;
	bus_dmamap_t msg_map;
	bus_addr_t msg_phys;
	uint32_t reg;
	device_t mbox;
	int err;

	/* get mbox device */
	mbox = devclass_get_device(devclass_find("mbox"), 0);
	if (mbox == NULL)
		return (ENXIO);

	sc = device_get_softc(mbox);
	sx_xlock(&sc->property_chan_lock);

	/* Allocate memory for the message */
	buf = bcm2835_mbox_init_dma(mbox, msg_size, &msg_tag, &msg_map,
	    &msg_phys);
	if (buf == NULL) {
		err = ENOMEM;
		goto out;
	}

	memcpy(buf, msg, msg_size);

	bus_dmamap_sync(msg_tag, msg_map,
	    BUS_DMASYNC_PREWRITE);

	MBOX_WRITE(mbox, BCM2835_MBOX_CHAN_PROP, (uint32_t)msg_phys);
	MBOX_READ(mbox, BCM2835_MBOX_CHAN_PROP, &reg);

	bus_dmamap_sync(msg_tag, msg_map,
	    BUS_DMASYNC_PREREAD);

	memcpy(msg, buf, msg_size);

	err = bcm2835_mbox_err(mbox, msg_phys, reg,
	    (struct bcm2835_mbox_hdr *)msg, msg_size);

	bus_dmamap_unload(msg_tag, msg_map);
	bus_dmamem_free(msg_tag, buf, msg_map);
	bus_dma_tag_destroy(msg_tag);
out:
	sx_xunlock(&sc->property_chan_lock);
	return (err);
}