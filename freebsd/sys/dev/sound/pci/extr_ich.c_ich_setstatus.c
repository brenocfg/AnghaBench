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
struct sc_info {int flags; int /*<<< orphan*/  dev; int /*<<< orphan*/  bufsz; int /*<<< orphan*/  irq; int /*<<< orphan*/  nabmbar; int /*<<< orphan*/  nambar; } ;

/* Variables and functions */
 int ICH_DMA_NOCACHE ; 
 int /*<<< orphan*/  PCM_KLDSTRING (int /*<<< orphan*/ ) ; 
 int SND_STATUSLEN ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pcm_setstatus (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rman_get_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ich ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ich_setstatus(struct sc_info *sc)
{
	char status[SND_STATUSLEN];

	snprintf(status, SND_STATUSLEN,
	    "at io 0x%jx, 0x%jx irq %jd bufsz %u %s",
	    rman_get_start(sc->nambar), rman_get_start(sc->nabmbar),
	    rman_get_start(sc->irq), sc->bufsz,PCM_KLDSTRING(snd_ich));

	if (bootverbose && (sc->flags & ICH_DMA_NOCACHE))
		device_printf(sc->dev,
		    "PCI Master abort workaround enabled\n");

	pcm_setstatus(sc->dev, status);
}