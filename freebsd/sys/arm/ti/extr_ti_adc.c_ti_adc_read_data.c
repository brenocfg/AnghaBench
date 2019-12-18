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
struct ti_adc_softc {int dummy; } ;
struct ti_adc_input {scalar_t__ enable; scalar_t__ value; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADC_FIFO0COUNT ; 
 int /*<<< orphan*/  ADC_FIFO0DATA ; 
 int ADC_FIFO_COUNT_MSK ; 
 int ADC_FIFO_DATA_MSK ; 
 int ADC_FIFO_STEP_ID_MSK ; 
 int ADC_FIFO_STEP_ID_SHIFT ; 
 int ADC_READ4 (struct ti_adc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TI_ADC_LOCK_ASSERT (struct ti_adc_softc*) ; 
 struct ti_adc_input* ti_adc_inputs ; 

__attribute__((used)) static void
ti_adc_read_data(struct ti_adc_softc *sc)
{
	int count, ain;
	struct ti_adc_input *input;
	uint32_t data;

	TI_ADC_LOCK_ASSERT(sc);

	/* Read the available data. */
	count = ADC_READ4(sc, ADC_FIFO0COUNT) & ADC_FIFO_COUNT_MSK;
	while (count > 0) {
		data = ADC_READ4(sc, ADC_FIFO0DATA);
		ain = (data & ADC_FIFO_STEP_ID_MSK) >> ADC_FIFO_STEP_ID_SHIFT;
		input = &ti_adc_inputs[ain];
		if (input->enable == 0)
			input->value = 0;
		else
			input->value = (int32_t)(data & ADC_FIFO_DATA_MSK);
		count = ADC_READ4(sc, ADC_FIFO0COUNT) & ADC_FIFO_COUNT_MSK;
	}
}