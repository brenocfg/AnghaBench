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
struct a10codec_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A10_ADCLEN ; 
 int /*<<< orphan*/  A10_ADCREN ; 
 int /*<<< orphan*/  A10_ADC_ACTL ; 
 int /*<<< orphan*/  A10_DACALEN ; 
 int /*<<< orphan*/  A10_DACAREN ; 
 int /*<<< orphan*/  A10_DACPAS ; 
 int /*<<< orphan*/  A10_DAC_ACTL ; 
 int /*<<< orphan*/  A10_PREG1EN ; 
 int /*<<< orphan*/  A10_VMICEN ; 
 int /*<<< orphan*/  CODEC_READ (struct a10codec_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CODEC_WRITE (struct a10codec_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PCMDIR_PLAY ; 

__attribute__((used)) static void
a10_mute(struct a10codec_info *sc, int mute, int dir)
{
	uint32_t val;

	if (dir == PCMDIR_PLAY) {
		val = CODEC_READ(sc, A10_DAC_ACTL);
		if (mute) {
			/* Disable DAC analog l/r channels and output mixer */
			val &= ~A10_DACAREN;
			val &= ~A10_DACALEN;
			val &= ~A10_DACPAS;
		} else {
			/* Enable DAC analog l/r channels and output mixer */
			val |= A10_DACAREN;
			val |= A10_DACALEN;
			val |= A10_DACPAS;
		}
		CODEC_WRITE(sc, A10_DAC_ACTL, val);
	} else {
		val = CODEC_READ(sc, A10_ADC_ACTL);
		if (mute) {
			/* Disable ADC analog l/r channels, MIC1 preamp,
			 * and VMIC pin voltage
			 */
			val &= ~A10_ADCREN;
			val &= ~A10_ADCLEN;
			val &= ~A10_PREG1EN;
			val &= ~A10_VMICEN;
		} else {
			/* Enable ADC analog l/r channels, MIC1 preamp,
			 * and VMIC pin voltage
			 */
			val |= A10_ADCREN;
			val |= A10_ADCLEN;
			val |= A10_PREG1EN;
			val |= A10_VMICEN;
		}
		CODEC_WRITE(sc, A10_ADC_ACTL, val);
	}
}