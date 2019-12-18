#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  dma_active; int /*<<< orphan*/  fmt; int /*<<< orphan*/  blksz; int /*<<< orphan*/  spd; } ;
struct sc_info {TYPE_1__ pch; TYPE_1__ rch; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  adcdac_go (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int cs4281_init (struct sc_info*) ; 
 int /*<<< orphan*/  cs4281_power (struct sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs4281chan_setblocksize (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs4281chan_setformat (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs4281chan_setspeed (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int mixer_reinit (int /*<<< orphan*/ ) ; 
 struct sc_info* pcm_getdevinfo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cs4281_pci_resume(device_t dev)
{
    struct sc_info *sc;

    sc = pcm_getdevinfo(dev);

    /* power up */
    cs4281_power(sc, 0);

    /* initialize chip */
    if (cs4281_init(sc) == -1) {
        device_printf(dev, "unable to reinitialize the card\n");
        return ENXIO;
    }

    /* restore mixer state */
    if (mixer_reinit(dev) == -1) {
	device_printf(dev, "unable to reinitialize the mixer\n");
	return ENXIO;
    }

    /* restore chip state */
    cs4281chan_setspeed(NULL, &sc->rch, sc->rch.spd);
    cs4281chan_setblocksize(NULL, &sc->rch, sc->rch.blksz);
    cs4281chan_setformat(NULL, &sc->rch, sc->rch.fmt);
    adcdac_go(&sc->rch, sc->rch.dma_active);

    cs4281chan_setspeed(NULL, &sc->pch, sc->pch.spd);
    cs4281chan_setblocksize(NULL, &sc->pch, sc->pch.blksz);
    cs4281chan_setformat(NULL, &sc->pch, sc->pch.fmt);
    adcdac_go(&sc->pch, sc->pch.dma_active);

    return 0;
}