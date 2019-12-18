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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct hdac_softc {TYPE_2__* streams; int /*<<< orphan*/  mem; } ;
struct hdac_bdle {void* ioc; void* len; void* addrh; void* addrl; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ bus_addr_t ;
struct TYPE_3__ {int dma_paddr; int /*<<< orphan*/  dma_map; int /*<<< orphan*/  dma_tag; scalar_t__ dma_vaddr; } ;
struct TYPE_4__ {int stripe; int format; int blksz; int running; TYPE_1__ bdl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 scalar_t__ HDAC_INTCTL ; 
 int HDAC_READ_1 (int /*<<< orphan*/ *,scalar_t__) ; 
 int HDAC_READ_4 (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ HDAC_SDBDPL ; 
 scalar_t__ HDAC_SDBDPU ; 
 scalar_t__ HDAC_SDCBL ; 
 scalar_t__ HDAC_SDCTL0 ; 
 scalar_t__ HDAC_SDCTL2 ; 
 int HDAC_SDCTL2_DIR ; 
 int HDAC_SDCTL2_STRIPE_MASK ; 
 int HDAC_SDCTL2_STRIPE_SHIFT ; 
 int HDAC_SDCTL2_STRM_MASK ; 
 int HDAC_SDCTL2_STRM_SHIFT ; 
 int HDAC_SDCTL_DEIE ; 
 int HDAC_SDCTL_FEIE ; 
 int HDAC_SDCTL_IOCE ; 
 int HDAC_SDCTL_RUN ; 
 scalar_t__ HDAC_SDFMT ; 
 scalar_t__ HDAC_SDLVI ; 
 scalar_t__ HDAC_SDSTS ; 
 int HDAC_SDSTS_BCIS ; 
 int HDAC_SDSTS_DESE ; 
 int HDAC_SDSTS_FIFOE ; 
 int /*<<< orphan*/  HDAC_WRITE_1 (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  HDAC_WRITE_2 (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  HDAC_WRITE_4 (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hdac_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int hdac_find_stream (struct hdac_softc*,int,int) ; 
 int /*<<< orphan*/  hdac_poll_reinit (struct hdac_softc*) ; 
 void* htole32 (int) ; 

__attribute__((used)) static int
hdac_stream_start(device_t dev, device_t child,
    int dir, int stream, bus_addr_t buf, int blksz, int blkcnt)
{
	struct hdac_softc *sc = device_get_softc(dev);
	struct hdac_bdle *bdle;
	uint64_t addr;
	int i, ss, off;
	uint32_t ctl;

	ss = hdac_find_stream(sc, dir, stream);
	KASSERT(ss >= 0,
	    ("Start for not allocated stream (%d/%d)\n", dir, stream));

	addr = (uint64_t)buf;
	bdle = (struct hdac_bdle *)sc->streams[ss].bdl.dma_vaddr;
	for (i = 0; i < blkcnt; i++, bdle++) {
		bdle->addrl = htole32((uint32_t)addr);
		bdle->addrh = htole32((uint32_t)(addr >> 32));
		bdle->len = htole32(blksz);
		bdle->ioc = htole32(1);
		addr += blksz;
	}

	bus_dmamap_sync(sc->streams[ss].bdl.dma_tag,
	    sc->streams[ss].bdl.dma_map, BUS_DMASYNC_PREWRITE);

	off = ss << 5;
	HDAC_WRITE_4(&sc->mem, off + HDAC_SDCBL, blksz * blkcnt);
	HDAC_WRITE_2(&sc->mem, off + HDAC_SDLVI, blkcnt - 1);
	addr = sc->streams[ss].bdl.dma_paddr;
	HDAC_WRITE_4(&sc->mem, off + HDAC_SDBDPL, (uint32_t)addr);
	HDAC_WRITE_4(&sc->mem, off + HDAC_SDBDPU, (uint32_t)(addr >> 32));

	ctl = HDAC_READ_1(&sc->mem, off + HDAC_SDCTL2);
	if (dir)
		ctl |= HDAC_SDCTL2_DIR;
	else
		ctl &= ~HDAC_SDCTL2_DIR;
	ctl &= ~HDAC_SDCTL2_STRM_MASK;
	ctl |= stream << HDAC_SDCTL2_STRM_SHIFT;
	ctl &= ~HDAC_SDCTL2_STRIPE_MASK;
	ctl |= sc->streams[ss].stripe << HDAC_SDCTL2_STRIPE_SHIFT;
	HDAC_WRITE_1(&sc->mem, off + HDAC_SDCTL2, ctl);

	HDAC_WRITE_2(&sc->mem, off + HDAC_SDFMT, sc->streams[ss].format);

	ctl = HDAC_READ_4(&sc->mem, HDAC_INTCTL);
	ctl |= 1 << ss;
	HDAC_WRITE_4(&sc->mem, HDAC_INTCTL, ctl);

	HDAC_WRITE_1(&sc->mem, off + HDAC_SDSTS,
	    HDAC_SDSTS_DESE | HDAC_SDSTS_FIFOE | HDAC_SDSTS_BCIS);
	ctl = HDAC_READ_1(&sc->mem, off + HDAC_SDCTL0);
	ctl |= HDAC_SDCTL_IOCE | HDAC_SDCTL_FEIE | HDAC_SDCTL_DEIE |
	    HDAC_SDCTL_RUN;
	HDAC_WRITE_1(&sc->mem, off + HDAC_SDCTL0, ctl);

	sc->streams[ss].blksz = blksz;
	sc->streams[ss].running = 1;
	hdac_poll_reinit(sc);
	return (0);
}