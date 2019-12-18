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
struct a10codec_info {int dummy; } ;

/* Variables and functions */
 int H3_ADCLEN ; 
 int H3_ADCREN ; 
 int /*<<< orphan*/  H3_ADC_AP_EN ; 
 int H3_DACALEN ; 
 int H3_DACAREN ; 
 int /*<<< orphan*/  H3_DAC_PA_SRC ; 
 int H3_LMIXEN ; 
 int /*<<< orphan*/  H3_LOMIXSC ; 
 int H3_LOMIXSC_LDAC ; 
 int H3_RMIXEN ; 
 int /*<<< orphan*/  H3_ROMIXSC ; 
 int H3_ROMIXSC_RDAC ; 
 int PCMDIR_PLAY ; 
 int /*<<< orphan*/  h3_pr_set_clear (struct a10codec_info*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
h3_mute(struct a10codec_info *sc, int mute, int dir)
{
	if (dir == PCMDIR_PLAY) {
		if (mute) {
			/* Mute DAC l/r channels to output mixer */
			h3_pr_set_clear(sc, H3_LOMIXSC, 0, H3_LOMIXSC_LDAC);
			h3_pr_set_clear(sc, H3_ROMIXSC, 0, H3_ROMIXSC_RDAC);
			/* Disable DAC analog l/r channels and output mixer */
			h3_pr_set_clear(sc, H3_DAC_PA_SRC,
			    0, H3_DACAREN | H3_DACALEN | H3_RMIXEN | H3_LMIXEN);
		} else {
			/* Enable DAC analog l/r channels and output mixer */
			h3_pr_set_clear(sc, H3_DAC_PA_SRC,
			    H3_DACAREN | H3_DACALEN | H3_RMIXEN | H3_LMIXEN, 0);
			/* Unmute DAC l/r channels to output mixer */
			h3_pr_set_clear(sc, H3_LOMIXSC, H3_LOMIXSC_LDAC, 0);
			h3_pr_set_clear(sc, H3_ROMIXSC, H3_ROMIXSC_RDAC, 0);
		}
	} else {
		if (mute) {
			/* Disable ADC analog l/r channels */
			h3_pr_set_clear(sc, H3_ADC_AP_EN,
			    0, H3_ADCREN | H3_ADCLEN);
		} else {
			/* Enable ADC analog l/r channels */
			h3_pr_set_clear(sc, H3_ADC_AP_EN,
			    H3_ADCREN | H3_ADCLEN, 0);
		}
	}
}