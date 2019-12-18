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
struct aml8726_sdxc_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AML_SDXC_IRQ_ENABLE_REG ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct aml8726_sdxc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aml8726_sdxc_power_off (struct aml8726_sdxc_softc*) ; 
 int /*<<< orphan*/  aml8726_sdxc_soft_reset (struct aml8726_sdxc_softc*) ; 
 struct aml8726_sdxc_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aml8726_sdxc_shutdown(device_t dev)
{
	struct aml8726_sdxc_softc *sc = device_get_softc(dev);

	/*
	 * Turn off the power, reset the hardware state machine,
	 * and disable the interrupts.
	 */
	aml8726_sdxc_power_off(sc);
	aml8726_sdxc_soft_reset(sc);
	CSR_WRITE_4(sc, AML_SDXC_IRQ_ENABLE_REG, 0);

	return (0);
}