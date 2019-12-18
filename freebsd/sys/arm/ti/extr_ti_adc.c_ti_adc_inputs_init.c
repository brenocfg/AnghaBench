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
struct ti_adc_softc {int sc_adc_nchannels; int* sc_adc_channels; } ;
struct ti_adc_input {int input; scalar_t__ samples; scalar_t__ enable; scalar_t__ value; struct ti_adc_softc* sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  TI_ADC_LOCK (struct ti_adc_softc*) ; 
 int /*<<< orphan*/  TI_ADC_UNLOCK (struct ti_adc_softc*) ; 
 int /*<<< orphan*/  ti_adc_input_setup (struct ti_adc_softc*,int) ; 
 struct ti_adc_input* ti_adc_inputs ; 

__attribute__((used)) static void
ti_adc_inputs_init(struct ti_adc_softc *sc)
{
	int ain, i;
	struct ti_adc_input *input;

	TI_ADC_LOCK(sc);
	for (i = 0; i < sc->sc_adc_nchannels; i++) {
		ain = sc->sc_adc_channels[i];
		input = &ti_adc_inputs[ain];
		input->sc = sc;
		input->input = ain;
		input->value = 0;
		input->enable = 0;
		input->samples = 0;
		ti_adc_input_setup(sc, ain);
	}
	TI_ADC_UNLOCK(sc);
}