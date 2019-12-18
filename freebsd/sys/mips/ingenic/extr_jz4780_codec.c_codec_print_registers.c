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
struct codec_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AICR_ADC ; 
 int /*<<< orphan*/  AICR_DAC ; 
 int /*<<< orphan*/  CR_ADC ; 
 int /*<<< orphan*/  CR_ADC_AGC ; 
 int /*<<< orphan*/  CR_CK ; 
 int /*<<< orphan*/  CR_DAC ; 
 int /*<<< orphan*/  CR_DMIC ; 
 int /*<<< orphan*/  CR_HP ; 
 int /*<<< orphan*/  CR_LI1 ; 
 int /*<<< orphan*/  CR_LI2 ; 
 int /*<<< orphan*/  CR_LO ; 
 int /*<<< orphan*/  CR_MIC1 ; 
 int /*<<< orphan*/  CR_MIC2 ; 
 int /*<<< orphan*/  CR_MIX ; 
 int /*<<< orphan*/  CR_TIMER_LSB ; 
 int /*<<< orphan*/  CR_TIMER_MSB ; 
 int /*<<< orphan*/  CR_VIC ; 
 int /*<<< orphan*/  DR_ADC_AGC ; 
 int /*<<< orphan*/  DR_MIX ; 
 int /*<<< orphan*/  FCR_ADC ; 
 int /*<<< orphan*/  FCR_DAC ; 
 int /*<<< orphan*/  GCR_ADCL ; 
 int /*<<< orphan*/  GCR_ADCR ; 
 int /*<<< orphan*/  GCR_DACL ; 
 int /*<<< orphan*/  GCR_DACR ; 
 int /*<<< orphan*/  GCR_HPL ; 
 int /*<<< orphan*/  GCR_HPR ; 
 int /*<<< orphan*/  GCR_LIBYL ; 
 int /*<<< orphan*/  GCR_LIBYR ; 
 int /*<<< orphan*/  GCR_MIC1 ; 
 int /*<<< orphan*/  GCR_MIC2 ; 
 int /*<<< orphan*/  GCR_MIXADCL ; 
 int /*<<< orphan*/  GCR_MIXADCR ; 
 int /*<<< orphan*/  GCR_MIXDACL ; 
 int /*<<< orphan*/  GCR_MIXDACR ; 
 int /*<<< orphan*/  ICR ; 
 int /*<<< orphan*/  IFR ; 
 int /*<<< orphan*/  IFR2 ; 
 int /*<<< orphan*/  IMR ; 
 int /*<<< orphan*/  IMR2 ; 
 int /*<<< orphan*/  MR ; 
 int /*<<< orphan*/  SR ; 
 int /*<<< orphan*/  SR2 ; 
 int codec_read (struct codec_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

void
codec_print_registers(struct codec_softc *sc)
{

	printf("codec SR %x\n", codec_read(sc, SR));
	printf("codec SR2 %x\n", codec_read(sc, SR2));
	printf("codec MR %x\n", codec_read(sc, MR));
	printf("codec AICR_DAC %x\n", codec_read(sc, AICR_DAC));
	printf("codec AICR_ADC %x\n", codec_read(sc, AICR_ADC));
	printf("codec CR_LO %x\n", codec_read(sc, CR_LO));
	printf("codec CR_HP %x\n", codec_read(sc, CR_HP));
	printf("codec CR_DMIC %x\n", codec_read(sc, CR_DMIC));
	printf("codec CR_MIC1 %x\n", codec_read(sc, CR_MIC1));
	printf("codec CR_MIC2 %x\n", codec_read(sc, CR_MIC2));
	printf("codec CR_LI1 %x\n", codec_read(sc, CR_LI1));
	printf("codec CR_LI2 %x\n", codec_read(sc, CR_LI2));
	printf("codec CR_DAC %x\n", codec_read(sc, CR_DAC));
	printf("codec CR_ADC %x\n", codec_read(sc, CR_ADC));
	printf("codec CR_MIX %x\n", codec_read(sc, CR_MIX));
	printf("codec DR_MIX %x\n", codec_read(sc, DR_MIX));
	printf("codec CR_VIC %x\n", codec_read(sc, CR_VIC));
	printf("codec CR_CK %x\n", codec_read(sc, CR_CK));
	printf("codec FCR_DAC %x\n", codec_read(sc, FCR_DAC));
	printf("codec FCR_ADC %x\n", codec_read(sc, FCR_ADC));
	printf("codec CR_TIMER_MSB %x\n", codec_read(sc, CR_TIMER_MSB));
	printf("codec CR_TIMER_LSB %x\n", codec_read(sc, CR_TIMER_LSB));
	printf("codec ICR %x\n", codec_read(sc, ICR));
	printf("codec IMR %x\n", codec_read(sc, IMR));
	printf("codec IFR %x\n", codec_read(sc, IFR));
	printf("codec IMR2 %x\n", codec_read(sc, IMR2));
	printf("codec IFR2 %x\n", codec_read(sc, IFR2));
	printf("codec GCR_HPL %x\n", codec_read(sc, GCR_HPL));
	printf("codec GCR_HPR %x\n", codec_read(sc, GCR_HPR));
	printf("codec GCR_LIBYL %x\n", codec_read(sc, GCR_LIBYL));
	printf("codec GCR_LIBYR %x\n", codec_read(sc, GCR_LIBYR));
	printf("codec GCR_DACL %x\n", codec_read(sc, GCR_DACL));
	printf("codec GCR_DACR %x\n", codec_read(sc, GCR_DACR));
	printf("codec GCR_MIC1 %x\n", codec_read(sc, GCR_MIC1));
	printf("codec GCR_MIC2 %x\n", codec_read(sc, GCR_MIC2));
	printf("codec GCR_ADCL %x\n", codec_read(sc, GCR_ADCL));
	printf("codec GCR_ADCR %x\n", codec_read(sc, GCR_ADCR));
	printf("codec GCR_MIXDACL %x\n", codec_read(sc, GCR_MIXDACL));
	printf("codec GCR_MIXDACR %x\n", codec_read(sc, GCR_MIXDACR));
	printf("codec GCR_MIXADCL %x\n", codec_read(sc, GCR_MIXADCL));
	printf("codec GCR_MIXADCR %x\n", codec_read(sc, GCR_MIXADCR));
	printf("codec CR_ADC_AGC %x\n", codec_read(sc, CR_ADC_AGC));
	printf("codec DR_ADC_AGC %x\n", codec_read(sc, DR_ADC_AGC));
}