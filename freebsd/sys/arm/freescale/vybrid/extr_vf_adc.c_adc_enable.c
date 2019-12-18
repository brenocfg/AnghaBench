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
struct adc_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADC_HC0 ; 
 int HC_ADCH_M ; 
 int HC_ADCH_S ; 
 int READ4 (struct adc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE4 (struct adc_softc*,int /*<<< orphan*/ ,int) ; 
 struct adc_softc* adc_sc ; 

uint32_t
adc_enable(int channel)
{
	struct adc_softc *sc;
	int reg;

	sc = adc_sc;
	if (sc == NULL)
		return (1);

	reg = READ4(sc, ADC_HC0);
	reg &= ~(HC_ADCH_M << HC_ADCH_S);
	reg |= (channel << HC_ADCH_S);
	WRITE4(sc, ADC_HC0, reg);

	return (0);
}