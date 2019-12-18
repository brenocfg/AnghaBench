#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/ * ich_func; } ;
struct atiixp_info {int polling; int codec_not_ready_bits; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  reg; int /*<<< orphan*/ * codec; int /*<<< orphan*/  codec_found; scalar_t__ codec_idx; int /*<<< orphan*/  lock; TYPE_1__ delayed_attach; } ;

/* Variables and functions */
 int /*<<< orphan*/ * AC97_CREATE (int /*<<< orphan*/ ,struct atiixp_info*,int /*<<< orphan*/ ) ; 
 int AC97_F_EAPD_INV ; 
 int ATI_IXP_NPCHAN ; 
 int ATI_IXP_NRCHAN ; 
 int ATI_REG_ISR_CODEC0_NOT_READY ; 
 int ATI_REG_ISR_CODEC1_NOT_READY ; 
 int ATI_REG_ISR_CODEC2_NOT_READY ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  PCMDIR_PLAY ; 
 int /*<<< orphan*/  PCMDIR_REC ; 
 int /*<<< orphan*/  PCM_KLDSTRING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PWAIT ; 
 int SND_STATUSLEN ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int ac97_getflags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ac97_getmixerclass () ; 
 int /*<<< orphan*/  ac97_setflags (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atiixp_ac97 ; 
 int /*<<< orphan*/  atiixp_chan_class ; 
 int /*<<< orphan*/  atiixp_disable_interrupts (struct atiixp_info*) ; 
 int /*<<< orphan*/  atiixp_enable_interrupts (struct atiixp_info*) ; 
 int /*<<< orphan*/  atiixp_lock (struct atiixp_info*) ; 
 int /*<<< orphan*/  atiixp_release_resource (struct atiixp_info*) ; 
 int /*<<< orphan*/  atiixp_unlock (struct atiixp_info*) ; 
 int /*<<< orphan*/  config_intrhook_disestablish (TYPE_1__*) ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hz ; 
 int /*<<< orphan*/  max (int,int) ; 
 int /*<<< orphan*/  mixer_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (struct atiixp_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int pci_get_subdevice (int /*<<< orphan*/ ) ; 
 int pci_get_subvendor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm_addchan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct atiixp_info*) ; 
 scalar_t__ pcm_register (int /*<<< orphan*/ ,struct atiixp_info*,int,int) ; 
 int /*<<< orphan*/  pcm_setstatus (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rman_get_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_atiixp ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysctl_atiixp_polling ; 

__attribute__((used)) static void
atiixp_chip_post_init(void *arg)
{
	struct atiixp_info *sc = (struct atiixp_info *)arg;
	uint32_t subdev;
	int i, timeout, found, polling;
	char status[SND_STATUSLEN];

	atiixp_lock(sc);

	if (sc->delayed_attach.ich_func) {
		config_intrhook_disestablish(&sc->delayed_attach);
		sc->delayed_attach.ich_func = NULL;
	}

	polling = sc->polling;
	sc->polling = 0;

	timeout = 10;
	if (sc->codec_not_ready_bits == 0) {
		/* wait for the interrupts to happen */
		do {
			msleep(sc, sc->lock, PWAIT, "ixpslp", max(hz / 10, 1));
			if (sc->codec_not_ready_bits != 0)
				break;
		} while (--timeout);
	}

	sc->polling = polling;
	atiixp_disable_interrupts(sc);

	if (sc->codec_not_ready_bits == 0 && timeout == 0) {
		device_printf(sc->dev,
			"WARNING: timeout during codec detection; "
			"codecs might be present but haven't interrupted\n");
		atiixp_unlock(sc);
		goto postinitbad;
	}

	found = 0;

	/*
	 * ATI IXP can have upto 3 codecs, but single codec should be
	 * suffice for now.
	 */
	if (!(sc->codec_not_ready_bits & ATI_REG_ISR_CODEC0_NOT_READY)) {
		/* codec 0 present */
		sc->codec_found++;
		sc->codec_idx = 0;
		found++;
	}

	if (!(sc->codec_not_ready_bits & ATI_REG_ISR_CODEC1_NOT_READY)) {
		/* codec 1 present */
		sc->codec_found++;
	}

	if (!(sc->codec_not_ready_bits & ATI_REG_ISR_CODEC2_NOT_READY)) {
		/* codec 2 present */
		sc->codec_found++;
	}

	atiixp_unlock(sc);

	if (found == 0)
		goto postinitbad;

	/* create/init mixer */
	sc->codec = AC97_CREATE(sc->dev, sc, atiixp_ac97);
	if (sc->codec == NULL)
		goto postinitbad;

	subdev = (pci_get_subdevice(sc->dev) << 16) |
	    pci_get_subvendor(sc->dev);
	switch (subdev) {
	case 0x11831043:	/* ASUS A6R */
	case 0x2043161f:	/* Maxselect x710s - http://maxselect.ru/ */
		ac97_setflags(sc->codec, ac97_getflags(sc->codec) |
		    AC97_F_EAPD_INV);
		break;
	default:
		break;
	}

	mixer_init(sc->dev, ac97_getmixerclass(), sc->codec);

	if (pcm_register(sc->dev, sc, ATI_IXP_NPCHAN, ATI_IXP_NRCHAN))
		goto postinitbad;

	for (i = 0; i < ATI_IXP_NPCHAN; i++)
		pcm_addchan(sc->dev, PCMDIR_PLAY, &atiixp_chan_class, sc);
	for (i = 0; i < ATI_IXP_NRCHAN; i++)
		pcm_addchan(sc->dev, PCMDIR_REC, &atiixp_chan_class, sc);

	SYSCTL_ADD_PROC(device_get_sysctl_ctx(sc->dev),
	    SYSCTL_CHILDREN(device_get_sysctl_tree(sc->dev)), OID_AUTO,
	    "polling", CTLTYPE_INT | CTLFLAG_RW, sc->dev, sizeof(sc->dev),
	    sysctl_atiixp_polling, "I", "Enable polling mode");

	snprintf(status, SND_STATUSLEN, "at memory 0x%jx irq %jd %s",
	    rman_get_start(sc->reg), rman_get_start(sc->irq),
	    PCM_KLDSTRING(snd_atiixp));

	pcm_setstatus(sc->dev, status);

	atiixp_lock(sc);
	if (sc->polling == 0)
		atiixp_enable_interrupts(sc);
	atiixp_unlock(sc);

	return;

postinitbad:
	atiixp_release_resource(sc);
}