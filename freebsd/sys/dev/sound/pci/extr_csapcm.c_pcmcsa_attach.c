#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct sndcard_func {TYPE_3__* varinfo; } ;
struct TYPE_12__ {int /*<<< orphan*/  irq; scalar_t__ irq_rid; void* mem_rid; void* io_rid; } ;
struct TYPE_9__ {int dma; } ;
struct TYPE_8__ {int dma; } ;
struct csa_info {int /*<<< orphan*/  ih; TYPE_4__* card; TYPE_5__ res; TYPE_3__* binfo; scalar_t__ active; TYPE_2__ rch; TYPE_1__ pch; } ;
struct ac97_info {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  TYPE_5__ csa_res ;
struct TYPE_11__ {scalar_t__ inv_eapd; } ;
struct TYPE_10__ {TYPE_4__* card; } ;

/* Variables and functions */
 struct ac97_info* AC97_CREATE (int /*<<< orphan*/ ,struct csa_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AC97_F_EAPD_INV ; 
 int /*<<< orphan*/  BA1_CIE ; 
 int /*<<< orphan*/  BA1_PFIE ; 
 int ENXIO ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 void* PCIR_BAR (int) ; 
 int /*<<< orphan*/  PCMDIR_PLAY ; 
 int /*<<< orphan*/  PCMDIR_REC ; 
 int /*<<< orphan*/  PCM_KLDSTRING (int /*<<< orphan*/ ) ; 
 int SND_STATUSLEN ; 
 int /*<<< orphan*/  ac97_destroy (struct ac97_info*) ; 
 int /*<<< orphan*/  ac97_getmixerclass () ; 
 int /*<<< orphan*/  ac97_setflags (struct ac97_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csa_ac97 ; 
 int /*<<< orphan*/  csa_active (struct csa_info*,int) ; 
 scalar_t__ csa_allocres (struct csa_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ csa_init (struct csa_info*) ; 
 int /*<<< orphan*/  csa_intr ; 
 int csa_readmem (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csa_releaseres (struct csa_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csa_writemem (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  csachan_class ; 
 struct sndcard_func* device_get_ivars (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 struct csa_info* malloc (int,int /*<<< orphan*/ ,int) ; 
 int mixer_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ac97_info*) ; 
 int /*<<< orphan*/  pcm_addchan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct csa_info*) ; 
 scalar_t__ pcm_register (int /*<<< orphan*/ ,struct csa_info*,int,int) ; 
 int /*<<< orphan*/  pcm_setstatus (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rman_get_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_csa ; 
 scalar_t__ snd_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct csa_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pcmcsa_attach(device_t dev)
{
	struct csa_info *csa;
	csa_res *resp;
	int unit;
	char status[SND_STATUSLEN];
	struct ac97_info *codec;
	struct sndcard_func *func;

	csa = malloc(sizeof(*csa), M_DEVBUF, M_WAITOK | M_ZERO);
	unit = device_get_unit(dev);
	func = device_get_ivars(dev);
	csa->binfo = func->varinfo;
	/*
	 * Fake the status of DMA so that the initial value of
	 * PCTL and CCTL can be stored into csa->pctl and csa->cctl,
	 * respectively.
	 */
	csa->pch.dma = csa->rch.dma = 1;
	csa->active = 0;
	csa->card = csa->binfo->card;

	/* Allocate the resources. */
	resp = &csa->res;
	resp->io_rid = PCIR_BAR(0);
	resp->mem_rid = PCIR_BAR(1);
	resp->irq_rid = 0;
	if (csa_allocres(csa, dev)) {
		csa_releaseres(csa, dev);
		return (ENXIO);
	}

	csa_active(csa, 1);
	if (csa_init(csa)) {
		csa_releaseres(csa, dev);
		return (ENXIO);
	}
	codec = AC97_CREATE(dev, csa, csa_ac97);
	if (codec == NULL) {
		csa_releaseres(csa, dev);
		return (ENXIO);
	}
	if (csa->card->inv_eapd)
		ac97_setflags(codec, AC97_F_EAPD_INV);
	if (mixer_init(dev, ac97_getmixerclass(), codec) == -1) {
		ac97_destroy(codec);
		csa_releaseres(csa, dev);
		return (ENXIO);
	}

	snprintf(status, SND_STATUSLEN, "at irq %jd %s",
			rman_get_start(resp->irq),PCM_KLDSTRING(snd_csa));

	/* Enable interrupt. */
	if (snd_setup_intr(dev, resp->irq, 0, csa_intr, csa, &csa->ih)) {
		ac97_destroy(codec);
		csa_releaseres(csa, dev);
		return (ENXIO);
	}
	csa_writemem(resp, BA1_PFIE, csa_readmem(resp, BA1_PFIE) & ~0x0000f03f);
	csa_writemem(resp, BA1_CIE, (csa_readmem(resp, BA1_CIE) & ~0x0000003f) | 0x00000001);
	csa_active(csa, -1);

	if (pcm_register(dev, csa, 1, 1)) {
		ac97_destroy(codec);
		csa_releaseres(csa, dev);
		return (ENXIO);
	}
	pcm_addchan(dev, PCMDIR_REC, &csachan_class, csa);
	pcm_addchan(dev, PCMDIR_PLAY, &csachan_class, csa);
	pcm_setstatus(dev, status);

	return (0);
}