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
typedef  int /*<<< orphan*/  uint8_t ;
struct elink_params {struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E3 (struct bxe_softc*) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P1 (struct bxe_softc*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elink_set_e1e2_module_fault_led (struct elink_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elink_set_e3_module_fault_led (struct elink_params*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void elink_set_sfp_module_fault_led(struct elink_params *params,
					   uint8_t gpio_mode)
{
	struct bxe_softc *sc = params->sc;
	ELINK_DEBUG_P1(sc, "Setting SFP+ module fault LED to %d\n", gpio_mode);
	if (CHIP_IS_E3(sc)) {
		/* Low ==> if SFP+ module is supported otherwise
		 * High ==> if SFP+ module is not on the approved vendor list
		 */
		elink_set_e3_module_fault_led(params, gpio_mode);
	} else
		elink_set_e1e2_module_fault_led(params, gpio_mode);
}