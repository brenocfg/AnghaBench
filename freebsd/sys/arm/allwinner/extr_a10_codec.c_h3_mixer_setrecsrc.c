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
 int H3_ADCMIXSC_LINEIN ; 
 int H3_ADCMIXSC_MIC1 ; 
 int H3_ADCMIXSC_MIC2 ; 
 int H3_ADCMIXSC_OMIXER ; 
 int /*<<< orphan*/  H3_LADCMIXSC ; 
 int /*<<< orphan*/  H3_RADCMIXSC ; 
 int SOUND_MASK_IMIX ; 
 int SOUND_MASK_LINE ; 
 int SOUND_MASK_LINE1 ; 
 int SOUND_MASK_MIC ; 
 int /*<<< orphan*/  h3_pr_write (struct a10codec_info*,int /*<<< orphan*/ ,int) ; 
 struct a10codec_info* mix_getdevinfo (struct snd_mixer*) ; 

__attribute__((used)) static uint32_t
h3_mixer_setrecsrc(struct snd_mixer *m, uint32_t src)
{
	struct a10codec_info *sc = mix_getdevinfo(m);
	uint32_t val;

	val = 0;
	src &= (SOUND_MASK_LINE | SOUND_MASK_MIC |
	    SOUND_MASK_LINE1 | SOUND_MASK_IMIX);

	if ((src & SOUND_MASK_LINE) != 0)	/* line-in */
		val |= H3_ADCMIXSC_LINEIN;
	if ((src & SOUND_MASK_MIC) != 0)	/* MIC1 */
		val |= H3_ADCMIXSC_MIC1;
	if ((src & SOUND_MASK_LINE1) != 0)	/* MIC2 */
		val |= H3_ADCMIXSC_MIC2;
	if ((src & SOUND_MASK_IMIX) != 0)	/* l/r output mixer */
		val |= H3_ADCMIXSC_OMIXER;

	h3_pr_write(sc, H3_LADCMIXSC, val);
	h3_pr_write(sc, H3_RADCMIXSC, val);

	return (src);
}