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
struct snd_mixer {int dummy; } ;
struct a10codec_info {int dummy; } ;

/* Variables and functions */
 int A10_ADCIS_MASK ; 
 int A10_ADCIS_SHIFT ; 
 int /*<<< orphan*/  A10_ADC_ACTL ; 
#define  A10_ADC_IS_LINEIN 133 
#define  A10_ADC_IS_MIC1 132 
#define  A10_ADC_IS_MIC2 131 
 int CODEC_READ (struct a10codec_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CODEC_WRITE (struct a10codec_info*,int /*<<< orphan*/ ,int) ; 
#define  SOUND_MASK_LINE 130 
#define  SOUND_MASK_LINE1 129 
#define  SOUND_MASK_MIC 128 
 struct a10codec_info* mix_getdevinfo (struct snd_mixer*) ; 

__attribute__((used)) static uint32_t
a10_mixer_setrecsrc(struct snd_mixer *m, uint32_t src)
{
	struct a10codec_info *sc = mix_getdevinfo(m);
	uint32_t val;

	val = CODEC_READ(sc, A10_ADC_ACTL);

	switch (src) {
	case SOUND_MASK_LINE:	/* line-in */
		val &= ~A10_ADCIS_MASK;
		val |= (A10_ADC_IS_LINEIN << A10_ADCIS_SHIFT);
		break;
	case SOUND_MASK_MIC:	/* MIC1 */
		val &= ~A10_ADCIS_MASK;
		val |= (A10_ADC_IS_MIC1 << A10_ADCIS_SHIFT);
		break;
	case SOUND_MASK_LINE1:	/* MIC2 */
		val &= ~A10_ADCIS_MASK;
		val |= (A10_ADC_IS_MIC2 << A10_ADCIS_SHIFT);
		break;
	default:
		break;
	}

	CODEC_WRITE(sc, A10_ADC_ACTL, val);

	switch ((val & A10_ADCIS_MASK) >> A10_ADCIS_SHIFT) {
	case A10_ADC_IS_LINEIN:
		return (SOUND_MASK_LINE);
	case A10_ADC_IS_MIC1:
		return (SOUND_MASK_MIC);
	case A10_ADC_IS_MIC2:
		return (SOUND_MASK_LINE1);
	default:
		return (0);
	}
}