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
typedef  int uint32_t ;
struct hdac_softc {TYPE_2__* streams; int /*<<< orphan*/  mem; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {int /*<<< orphan*/  dma_map; int /*<<< orphan*/  dma_tag; } ;
struct TYPE_4__ {scalar_t__ running; TYPE_1__ bdl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  HDAC_INTCTL ; 
 int HDAC_READ_1 (int /*<<< orphan*/ *,scalar_t__) ; 
 int HDAC_READ_4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ HDAC_SDCTL0 ; 
 int HDAC_SDCTL_DEIE ; 
 int HDAC_SDCTL_FEIE ; 
 int HDAC_SDCTL_IOCE ; 
 int HDAC_SDCTL_RUN ; 
 int /*<<< orphan*/  HDAC_WRITE_1 (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  HDAC_WRITE_4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hdac_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int hdac_find_stream (struct hdac_softc*,int,int) ; 
 int /*<<< orphan*/  hdac_poll_reinit (struct hdac_softc*) ; 

__attribute__((used)) static void
hdac_stream_stop(device_t dev, device_t child, int dir, int stream)
{
	struct hdac_softc *sc = device_get_softc(dev);
	int ss, off;
	uint32_t ctl;

	ss = hdac_find_stream(sc, dir, stream);
	KASSERT(ss >= 0,
	    ("Stop for not allocated stream (%d/%d)\n", dir, stream));

	bus_dmamap_sync(sc->streams[ss].bdl.dma_tag,
	    sc->streams[ss].bdl.dma_map, BUS_DMASYNC_POSTWRITE);

	off = ss << 5;
	ctl = HDAC_READ_1(&sc->mem, off + HDAC_SDCTL0);
	ctl &= ~(HDAC_SDCTL_IOCE | HDAC_SDCTL_FEIE | HDAC_SDCTL_DEIE |
	    HDAC_SDCTL_RUN);
	HDAC_WRITE_1(&sc->mem, off + HDAC_SDCTL0, ctl);

	ctl = HDAC_READ_4(&sc->mem, HDAC_INTCTL);
	ctl &= ~(1 << ss);
	HDAC_WRITE_4(&sc->mem, HDAC_INTCTL, ctl);

	sc->streams[ss].running = 0;
	hdac_poll_reinit(sc);
}