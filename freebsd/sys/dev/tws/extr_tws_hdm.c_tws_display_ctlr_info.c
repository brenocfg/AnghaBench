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
typedef  int /*<<< orphan*/  uint32_t ;
struct tws_softc {int /*<<< orphan*/  tws_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWS_PARAM_CONTROLLER_PHYS_COUNT ; 
 int /*<<< orphan*/  TWS_PARAM_CTLR_MODEL ; 
 int /*<<< orphan*/  TWS_PARAM_PHYS_TABLE ; 
 int /*<<< orphan*/  TWS_PARAM_VERSION_BIOS ; 
 int /*<<< orphan*/  TWS_PARAM_VERSION_FW ; 
 int /*<<< orphan*/  TWS_PARAM_VERSION_TABLE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tws_get_param (struct tws_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

void 
tws_display_ctlr_info(struct tws_softc *sc)
{

    uint8_t fw_ver[16], bios_ver[16], ctlr_model[16], num_phys=0;
    uint32_t error[4];

    error[0] = tws_get_param(sc, TWS_PARAM_PHYS_TABLE,
                             TWS_PARAM_CONTROLLER_PHYS_COUNT, 1, &num_phys);
    error[1] = tws_get_param(sc, TWS_PARAM_VERSION_TABLE,
                             TWS_PARAM_VERSION_FW, 16, fw_ver);
    error[2] = tws_get_param(sc, TWS_PARAM_VERSION_TABLE,
                             TWS_PARAM_VERSION_BIOS, 16, bios_ver);
    error[3] = tws_get_param(sc, TWS_PARAM_VERSION_TABLE,
                             TWS_PARAM_CTLR_MODEL, 16, ctlr_model);

    if ( !error[0] && !error[1] && !error[2] && !error[3] ) {
        device_printf( sc->tws_dev, 
        "Controller details: Model %.16s, %d Phys, Firmware %.16s, BIOS %.16s\n",
         ctlr_model, num_phys, fw_ver, bios_ver);
    }

}