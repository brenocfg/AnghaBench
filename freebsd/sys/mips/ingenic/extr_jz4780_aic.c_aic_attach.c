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
struct sc_pcminfo {scalar_t__ chnum; void* dev; struct aic_softc* sc; } ;
struct aic_softc {void* dev; int internal_codec; int /*<<< orphan*/  ih; int /*<<< orphan*/ * xchan; int /*<<< orphan*/ * res; scalar_t__ aic_fifo_paddr; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; int /*<<< orphan*/ * lock; int /*<<< orphan*/ * xdma_tx; scalar_t__ pos; } ;
typedef  void* device_t ;

/* Variables and functions */
 scalar_t__ AICDR ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int ENXIO ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  PCMDIR_PLAY ; 
 int SD_F_MPSAFE ; 
 int SND_STATUSLEN ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,struct sc_pcminfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int aic_configure (struct aic_softc*) ; 
 int aic_configure_clocks (struct aic_softc*) ; 
 int aic_dma_setup (struct aic_softc*) ; 
 int /*<<< orphan*/  aic_intr ; 
 int /*<<< orphan*/  aic_spec ; 
 int /*<<< orphan*/  aicchan_class ; 
 int /*<<< orphan*/  aicmixer_class ; 
 scalar_t__ bus_alloc_resources (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_nameunit (void*) ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (void*) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (void*) ; 
 int /*<<< orphan*/  device_printf (void*,char*) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mixer_init (void*,int /*<<< orphan*/ *,struct sc_pcminfo*) ; 
 char* ofw_bus_get_name (void*) ; 
 int /*<<< orphan*/  pcm_addchan (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sc_pcminfo*) ; 
 int pcm_getflags (void*) ; 
 int pcm_register (void*,struct sc_pcminfo*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm_setflags (void*,int) ; 
 int /*<<< orphan*/  pcm_setstatus (void*,char*) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 
 scalar_t__ rman_get_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * snd_mtxcreate (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  sysctl_hw_pcm_internal_codec ; 
 int /*<<< orphan*/ * xdma_channel_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdma_ofw_get (void*,char*) ; 
 int xdma_setup_intr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sc_pcminfo*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
aic_attach(device_t dev)
{
	char status[SND_STATUSLEN];
	struct sc_pcminfo *scp;
	struct aic_softc *sc;
	int err;

	sc = malloc(sizeof(*sc), M_DEVBUF, M_WAITOK | M_ZERO);
	sc->dev = dev;
	sc->pos = 0;
	sc->internal_codec = 1;

	/* Get xDMA controller */
	sc->xdma_tx = xdma_ofw_get(sc->dev, "tx");
	if (sc->xdma_tx == NULL) {
		device_printf(dev, "Can't find DMA controller.\n");
		return (ENXIO);
	}

	/* Alloc xDMA virtual channel. */
	sc->xchan = xdma_channel_alloc(sc->xdma_tx, 0);
	if (sc->xchan == NULL) {
		device_printf(dev, "Can't alloc virtual DMA channel.\n");
		return (ENXIO);
	}

	/* Setup sound subsystem */
	sc->lock = snd_mtxcreate(device_get_nameunit(dev), "aic softc");
	if (sc->lock == NULL) {
		device_printf(dev, "Can't create mtx.\n");
		return (ENXIO);
	}

	if (bus_alloc_resources(dev, aic_spec, sc->res)) {
		device_printf(dev,
		    "could not allocate resources for device\n");
		return (ENXIO);
	}

	/* Memory interface */
	sc->bst = rman_get_bustag(sc->res[0]);
	sc->bsh = rman_get_bushandle(sc->res[0]);
	sc->aic_fifo_paddr = rman_get_start(sc->res[0]) + AICDR;

	/* Setup PCM. */
	scp = malloc(sizeof(struct sc_pcminfo), M_DEVBUF, M_WAITOK | M_ZERO);
	scp->sc = sc;
	scp->dev = dev;

	/* Setup audio buffer. */
	err = aic_dma_setup(sc);
	if (err != 0) {
		device_printf(dev, "Can't setup sound buffer.\n");
		return (ENXIO);
	}

	/* Setup clocks. */
	err = aic_configure_clocks(sc);
	if (err != 0) {
		device_printf(dev, "Can't configure clocks.\n");
		return (ENXIO);
	}

	err = aic_configure(sc);
	if (err != 0) {
		device_printf(dev, "Can't configure AIC.\n");
		return (ENXIO);
	}

	pcm_setflags(dev, pcm_getflags(dev) | SD_F_MPSAFE);

	/* Setup interrupt handler. */
	err = xdma_setup_intr(sc->xchan, aic_intr, scp, &sc->ih);
	if (err) {
		device_printf(sc->dev,
		    "Can't setup xDMA interrupt handler.\n");
		return (ENXIO);
	}

	err = pcm_register(dev, scp, 1, 0);
	if (err) {
		device_printf(dev, "Can't register pcm.\n");
		return (ENXIO);
	}

	scp->chnum = 0;
	pcm_addchan(dev, PCMDIR_PLAY, &aicchan_class, scp);
	scp->chnum++;

	snprintf(status, SND_STATUSLEN, "at %s", ofw_bus_get_name(dev));
	pcm_setstatus(dev, status);

	mixer_init(dev, &aicmixer_class, scp);

	/* Create device sysctl node. */
	SYSCTL_ADD_PROC(device_get_sysctl_ctx(dev),
	    SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
	    OID_AUTO, "internal_codec", CTLTYPE_INT | CTLFLAG_RW,
	    scp, 0, sysctl_hw_pcm_internal_codec, "I",
	    "use internal audio codec");

	return (0);
}