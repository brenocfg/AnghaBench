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
struct a10hdmiaudio_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  dmat; int /*<<< orphan*/  dmasize; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  DMABUF_DEFAULT ; 
 int /*<<< orphan*/  DMABUF_MAX ; 
 int /*<<< orphan*/  DMABUF_MIN ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PCMDIR_PLAY ; 
 int SD_F_MPSAFE ; 
 int SD_F_SOFTPCMVOL ; 
 int SND_STATUSLEN ; 
 int /*<<< orphan*/  a10hdmiaudio_chan_class ; 
 int /*<<< orphan*/  a10hdmiaudio_mixer_class ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (struct a10hdmiaudio_info*,int /*<<< orphan*/ ) ; 
 struct a10hdmiaudio_info* malloc (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mixer_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct a10hdmiaudio_info*) ; 
 char* ofw_bus_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm_addchan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct a10hdmiaudio_info*) ; 
 int /*<<< orphan*/  pcm_getbuffersize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pcm_getflags (int /*<<< orphan*/ ) ; 
 scalar_t__ pcm_register (int /*<<< orphan*/ ,struct a10hdmiaudio_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm_setflags (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcm_setstatus (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_mtxcreate (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_mtxfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static int
a10hdmiaudio_attach(device_t dev)
{
	struct a10hdmiaudio_info *sc;
	char status[SND_STATUSLEN];
	int error;

	sc = malloc(sizeof(*sc), M_DEVBUF, M_WAITOK | M_ZERO);
	sc->dev = dev;
	sc->lock = snd_mtxcreate(device_get_nameunit(dev), "a10hdmiaudio softc");

	sc->dmasize = pcm_getbuffersize(dev, DMABUF_MIN,
	    DMABUF_DEFAULT, DMABUF_MAX);
	error = bus_dma_tag_create(
	    bus_get_dma_tag(dev),
	    4, sc->dmasize,		/* alignment, boundary */
	    BUS_SPACE_MAXADDR_32BIT,	/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    sc->dmasize, 1,		/* maxsize, nsegs */
	    sc->dmasize, 0,		/* maxsegsize, flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &sc->dmat);
	if (error != 0) {
		device_printf(dev, "cannot create DMA tag\n");
		goto fail;
	}

	if (mixer_init(dev, &a10hdmiaudio_mixer_class, sc)) {
		device_printf(dev, "mixer_init failed\n");
		goto fail;
	}

	pcm_setflags(dev, pcm_getflags(dev) | SD_F_MPSAFE);
	pcm_setflags(dev, pcm_getflags(dev) | SD_F_SOFTPCMVOL);

	if (pcm_register(dev, sc, 1, 0)) {
		device_printf(dev, "pcm_register failed\n");
		goto fail;
	}

	pcm_addchan(dev, PCMDIR_PLAY, &a10hdmiaudio_chan_class, sc);

	snprintf(status, SND_STATUSLEN, "at %s", ofw_bus_get_name(dev));
	pcm_setstatus(dev, status);

	return (0);

fail:
	snd_mtxfree(sc->lock);
	free(sc, M_DEVBUF);

	return (error);
}