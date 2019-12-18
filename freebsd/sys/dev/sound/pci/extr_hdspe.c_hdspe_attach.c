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
typedef  int uint32_t ;
struct sc_pcminfo {int /*<<< orphan*/  dev; struct sc_info* sc; struct hdspe_channel* hc; } ;
struct sc_info {int /*<<< orphan*/  type; int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; } ;
struct hdspe_channel {int /*<<< orphan*/ * descr; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AIO ; 
 int ENXIO ; 
 int HDSPE_MAX_CHANS ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
#define  PCI_REVISION_AIO 129 
#define  PCI_REVISION_RAYDAT 128 
 int /*<<< orphan*/  RAYDAT ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 struct hdspe_channel* chan_map_aio ; 
 struct hdspe_channel* chan_map_rd ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct sc_info* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ ,struct sc_pcminfo*) ; 
 int hdspe_alloc_resources (struct sc_info*) ; 
 scalar_t__ hdspe_init (struct sc_info*) ; 
 int /*<<< orphan*/  hdspe_map_dmabuf (struct sc_info*) ; 
 struct sc_pcminfo* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int pci_get_revid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxcreate (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
hdspe_attach(device_t dev)
{
	struct hdspe_channel *chan_map;
	struct sc_pcminfo *scp;
	struct sc_info *sc;
	uint32_t rev;
	int i, err;

#if 0
	device_printf(dev, "hdspe_attach()\n");
#endif

	sc = device_get_softc(dev);
	sc->lock = snd_mtxcreate(device_get_nameunit(dev),
	    "snd_hdspe softc");
	sc->dev = dev;

	pci_enable_busmaster(dev);
	rev = pci_get_revid(dev);
	switch (rev) {
	case PCI_REVISION_AIO:
		sc->type = AIO;
		chan_map = chan_map_aio;
		break;
	case PCI_REVISION_RAYDAT:
		sc->type = RAYDAT;
		chan_map = chan_map_rd;
		break;
	default:
		return (ENXIO);
	}

	/* Allocate resources. */
	err = hdspe_alloc_resources(sc);
	if (err) {
		device_printf(dev, "Unable to allocate system resources.\n");
		return (ENXIO);
	}

	if (hdspe_init(sc) != 0)
		return (ENXIO);

	for (i = 0; i < HDSPE_MAX_CHANS && chan_map[i].descr != NULL; i++) {
		scp = malloc(sizeof(struct sc_pcminfo), M_DEVBUF, M_NOWAIT | M_ZERO);
		scp->hc = &chan_map[i];
		scp->sc = sc;
		scp->dev = device_add_child(dev, "pcm", -1);
		device_set_ivars(scp->dev, scp);
	}

	hdspe_map_dmabuf(sc);

	return (bus_generic_attach(dev));
}