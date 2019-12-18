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
typedef  int /*<<< orphan*/  uint32_t ;
struct snd_mixer {int dummy; } ;
struct a10codec_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A10_ADC_ACTL ; 
 int /*<<< orphan*/  A10_DAC_ACTL ; 
 int /*<<< orphan*/  A10_PAMUTE ; 
 int /*<<< orphan*/  A10_PA_EN ; 
 int /*<<< orphan*/  CODEC_READ (struct a10codec_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CODEC_WRITE (struct a10codec_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SOUND_MASK_LINE ; 
 int SOUND_MASK_LINE1 ; 
 int SOUND_MASK_MIC ; 
 int SOUND_MASK_RECLEV ; 
 int SOUND_MASK_VOLUME ; 
 struct a10codec_info* mix_getdevinfo (struct snd_mixer*) ; 
 int /*<<< orphan*/  mix_setdevs (struct snd_mixer*,int) ; 
 int /*<<< orphan*/  mix_setrecdevs (struct snd_mixer*,int) ; 

__attribute__((used)) static int
a10_mixer_init(struct snd_mixer *m)
{
	struct a10codec_info *sc = mix_getdevinfo(m);
	uint32_t val;

	mix_setdevs(m, SOUND_MASK_VOLUME | SOUND_MASK_LINE | SOUND_MASK_RECLEV);
	mix_setrecdevs(m, SOUND_MASK_LINE | SOUND_MASK_LINE1 | SOUND_MASK_MIC);

	/* Unmute input source to PA */
	val = CODEC_READ(sc, A10_DAC_ACTL);
	val |= A10_PAMUTE;
	CODEC_WRITE(sc, A10_DAC_ACTL, val);

	/* Enable PA */
	val = CODEC_READ(sc, A10_ADC_ACTL);
	val |= A10_PA_EN;
	CODEC_WRITE(sc, A10_ADC_ACTL, val);

	return (0);
}