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
struct ti_adc_softc {int sc_xp_inp; int sc_xn_inp; int sc_yp_inp; int sc_yn_inp; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_yn_bit; int /*<<< orphan*/  sc_yp_bit; int /*<<< orphan*/  sc_xn_bit; int /*<<< orphan*/  sc_xp_bit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADC_STEP_XNN_SW ; 
 int /*<<< orphan*/  ADC_STEP_XPP_SW ; 
 int /*<<< orphan*/  ADC_STEP_YNN_SW ; 
 int /*<<< orphan*/  ADC_STEP_YPP_SW ; 
#define  ORDER_XN 131 
#define  ORDER_XP 130 
#define  ORDER_YN 129 
#define  ORDER_YP 128 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
ti_adc_config_wires(struct ti_adc_softc *sc, int *wire_configs, int nwire_configs)
{
	int i;
	int wire, ai;

	for (i = 0; i < nwire_configs; i++) {
		wire = wire_configs[i] & 0xf;
		ai = (wire_configs[i] >> 4) & 0xf;
		switch (wire) {
		case ORDER_XP:
			sc->sc_xp_bit = ADC_STEP_XPP_SW;
			sc->sc_xp_inp = ai;
			break;
		case ORDER_XN:
			sc->sc_xn_bit = ADC_STEP_XNN_SW;
			sc->sc_xn_inp = ai;
			break;
		case ORDER_YP:
			sc->sc_yp_bit = ADC_STEP_YPP_SW;
			sc->sc_yp_inp = ai;
			break;
		case ORDER_YN:
			sc->sc_yn_bit = ADC_STEP_YNN_SW;
			sc->sc_yn_inp = ai;
			break;
		default:
			device_printf(sc->sc_dev, "Invalid wire config\n");
			return (-1);
		}
	}
	return (0);
}