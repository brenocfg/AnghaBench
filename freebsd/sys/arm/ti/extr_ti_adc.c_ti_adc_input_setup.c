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
typedef  size_t uint32_t ;
struct ti_adc_softc {int dummy; } ;
struct ti_adc_input {size_t stepconfig; size_t samples; } ;
typedef  size_t int32_t ;

/* Variables and functions */
 size_t ADC_READ4 (struct ti_adc_softc*,size_t) ; 
 size_t ADC_STEP_AVG_MSK ; 
 size_t ADC_STEP_AVG_SHIFT ; 
 size_t ADC_STEP_DIFF_CNTRL ; 
 size_t ADC_STEP_INP_MSK ; 
 size_t ADC_STEP_INP_SHIFT ; 
 size_t ADC_STEP_MODE_MSK ; 
 size_t ADC_STEP_RFM_MSK ; 
 size_t ADC_STEP_RFP_MSK ; 
 int /*<<< orphan*/  ADC_WRITE4 (struct ti_adc_softc*,size_t,size_t) ; 
 int /*<<< orphan*/  TI_ADC_LOCK_ASSERT (struct ti_adc_softc*) ; 
 struct ti_adc_input* ti_adc_inputs ; 

__attribute__((used)) static void
ti_adc_input_setup(struct ti_adc_softc *sc, int32_t ain)
{
	struct ti_adc_input *input;
	uint32_t reg, val;

	TI_ADC_LOCK_ASSERT(sc);

	input = &ti_adc_inputs[ain];
	reg = input->stepconfig;
	val = ADC_READ4(sc, reg);

	/* Set single ended operation. */
	val &= ~ADC_STEP_DIFF_CNTRL;

	/* Set the negative voltage reference. */
	val &= ~ADC_STEP_RFM_MSK;

	/* Set the positive voltage reference. */
	val &= ~ADC_STEP_RFP_MSK;

	/* Set the samples average. */
	val &= ~ADC_STEP_AVG_MSK;
	val |= input->samples << ADC_STEP_AVG_SHIFT;

	/* Select the desired input. */
	val &= ~ADC_STEP_INP_MSK;
	val |= ain << ADC_STEP_INP_SHIFT;

	/* Set the ADC to one-shot mode. */
	val &= ~ADC_STEP_MODE_MSK;

	ADC_WRITE4(sc, reg, val);
}