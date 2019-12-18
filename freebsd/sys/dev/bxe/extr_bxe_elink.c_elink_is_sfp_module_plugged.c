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
typedef  scalar_t__ uint32_t ;
struct elink_phy {int dummy; } ;
struct elink_params {int /*<<< orphan*/  port; int /*<<< orphan*/  shmem_base; int /*<<< orphan*/  chip_id; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ ELINK_STATUS_OK ; 
 scalar_t__ elink_cb_gpio_read (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ elink_get_mod_abs_int_cfg (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int elink_is_sfp_module_plugged(struct elink_phy *phy,
				       struct elink_params *params)
{
	struct bxe_softc *sc = params->sc;
	uint8_t gpio_num, gpio_port;
	uint32_t gpio_val;
	if (elink_get_mod_abs_int_cfg(sc, params->chip_id,
				      params->shmem_base, params->port,
				      &gpio_num, &gpio_port) != ELINK_STATUS_OK)
		return 0;
	gpio_val = elink_cb_gpio_read(sc, gpio_num, gpio_port);

	/* Call the handling function in case module is detected */
	if (gpio_val == 0)
		return 1;
	else
		return 0;
}