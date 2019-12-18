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
struct iwm_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWM_CSR_LED_REG ; 
 int /*<<< orphan*/  IWM_CSR_LED_REG_TURN_OFF ; 
 int /*<<< orphan*/  IWM_WRITE (struct iwm_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
iwm_mvm_led_disable(struct iwm_softc *sc)
{
	IWM_WRITE(sc, IWM_CSR_LED_REG, IWM_CSR_LED_REG_TURN_OFF);
}