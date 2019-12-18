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
struct bcm2835_audio_info {int volume; int /*<<< orphan*/  pch; int /*<<< orphan*/  dev; int /*<<< orphan*/  dest; int /*<<< orphan*/  intr_hook; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEST_AUTO ; 
 int /*<<< orphan*/  PCMDIR_PLAY ; 
 int SND_STATUSLEN ; 
 int /*<<< orphan*/  bcm2835_audio_create_worker (struct bcm2835_audio_info*) ; 
 int /*<<< orphan*/  bcm2835_audio_init (struct bcm2835_audio_info*) ; 
 int /*<<< orphan*/  bcm2835_audio_open (struct bcm2835_audio_info*) ; 
 int /*<<< orphan*/  bcm2835_audio_reset_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcmchan_class ; 
 int /*<<< orphan*/  bcmmixer_class ; 
 int /*<<< orphan*/  config_intrhook_disestablish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mixer_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct bcm2835_audio_info*) ; 
 int /*<<< orphan*/  pcm_addchan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct bcm2835_audio_info*) ; 
 scalar_t__ pcm_register (int /*<<< orphan*/ ,struct bcm2835_audio_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm_setstatus (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*) ; 
 int /*<<< orphan*/  vchi_audio_sysctl_init (struct bcm2835_audio_info*) ; 

__attribute__((used)) static void
bcm2835_audio_delayed_init(void *xsc)
{
    	struct bcm2835_audio_info *sc;
    	char status[SND_STATUSLEN];

	sc = xsc;

	config_intrhook_disestablish(&sc->intr_hook);

	bcm2835_audio_init(sc);
	bcm2835_audio_open(sc);
	sc->volume = 75;
	sc->dest = DEST_AUTO;

    	if (mixer_init(sc->dev, &bcmmixer_class, sc)) {
		device_printf(sc->dev, "mixer_init failed\n");
		goto no;
	}

    	if (pcm_register(sc->dev, sc, 1, 0)) {
		device_printf(sc->dev, "pcm_register failed\n");
		goto no;
	}

	pcm_addchan(sc->dev, PCMDIR_PLAY, &bcmchan_class, sc);
    	snprintf(status, SND_STATUSLEN, "at VCHIQ");
	pcm_setstatus(sc->dev, status);

	bcm2835_audio_reset_channel(&sc->pch);
	bcm2835_audio_create_worker(sc);

	vchi_audio_sysctl_init(sc);

no:
	;
}