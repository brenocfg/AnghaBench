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
struct adc_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADC_R0 ; 
 int /*<<< orphan*/  READ4 (struct adc_softc*,int /*<<< orphan*/ ) ; 
 struct adc_softc* adc_sc ; 

uint32_t
adc_read(void)
{
	struct adc_softc *sc;

	sc = adc_sc;
	if (sc == NULL)
		return (0);

	return (READ4(sc, ADC_R0));
}