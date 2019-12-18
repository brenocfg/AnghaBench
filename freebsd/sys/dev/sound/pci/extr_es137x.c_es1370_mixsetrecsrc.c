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
struct snd_mixer {int dummy; } ;
struct es_info {int /*<<< orphan*/  escfg; } ;
struct TYPE_2__ {int recmask; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODEC_LIMIX1 ; 
 int /*<<< orphan*/  CODEC_LIMIX2 ; 
 int /*<<< orphan*/  CODEC_OMIX1 ; 
 int /*<<< orphan*/  CODEC_OMIX2 ; 
 int /*<<< orphan*/  CODEC_RIMIX1 ; 
 int /*<<< orphan*/  CODEC_RIMIX2 ; 
 scalar_t__ ES_DAC1_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ES_LOCK (struct es_info*) ; 
 scalar_t__ ES_SINGLE_PCM_MIX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ES_UNLOCK (struct es_info*) ; 
 int SOUND_MIXER_MIC ; 
 int SOUND_MIXER_NRDEVICES ; 
 int SOUND_MIXER_PCM ; 
 size_t SOUND_MIXER_SYNTH ; 
 int /*<<< orphan*/  es1370_wrcodec (struct es_info*,int /*<<< orphan*/ ,int) ; 
 struct es_info* mix_getdevinfo (struct snd_mixer*) ; 
 int mix_getrecdevs (struct snd_mixer*) ; 
 TYPE_1__* mixtable ; 

__attribute__((used)) static uint32_t
es1370_mixsetrecsrc(struct snd_mixer *m, uint32_t src)
{
	struct es_info *es;
	int i, j = 0;

	es = mix_getdevinfo(m);
	if (src == 0) src = 1 << SOUND_MIXER_MIC;
	src &= mix_getrecdevs(m);
	for (i = 0; i < SOUND_MIXER_NRDEVICES; i++)
		if ((src & (1 << i)) != 0) j |= mixtable[i].recmask;

	ES_LOCK(es);
	if ((src & (1 << SOUND_MIXER_PCM)) && ES_SINGLE_PCM_MIX(es->escfg) &&
	    ES_DAC1_ENABLED(es->escfg))
		j |= mixtable[SOUND_MIXER_SYNTH].recmask;
	es1370_wrcodec(es, CODEC_LIMIX1, j & 0x55);
	es1370_wrcodec(es, CODEC_RIMIX1, j & 0xaa);
	es1370_wrcodec(es, CODEC_LIMIX2, (j >> 8) & 0x17);
	es1370_wrcodec(es, CODEC_RIMIX2, (j >> 8) & 0x0f);
	es1370_wrcodec(es, CODEC_OMIX1, 0x7f);
	es1370_wrcodec(es, CODEC_OMIX2, 0x3f);
	ES_UNLOCK(es);

	return (src);
}