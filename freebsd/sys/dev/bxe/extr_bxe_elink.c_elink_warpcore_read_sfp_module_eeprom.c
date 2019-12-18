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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct elink_phy {int dummy; } ;
struct elink_params {struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;
typedef  scalar_t__ elink_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P0 (struct bxe_softc*,char*) ; 
 scalar_t__ ELINK_SFP_EEPROM_PAGE_SIZE ; 
 scalar_t__ ELINK_STATUS_ERROR ; 
 scalar_t__ ELINK_STATUS_OK ; 
 scalar_t__ I2C_WA_PWR_ITER ; 
 scalar_t__ I2C_WA_RETRY_CNT ; 
 int /*<<< orphan*/  elink_bsc_module_sel (struct elink_params*) ; 
 scalar_t__ elink_bsc_read (struct bxe_softc*,scalar_t__,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elink_warpcore_power_module (struct elink_params*,int) ; 

__attribute__((used)) static elink_status_t elink_warpcore_read_sfp_module_eeprom(struct elink_phy *phy,
						 struct elink_params *params,
						 uint8_t dev_addr,
						 uint16_t addr, uint8_t byte_cnt,
						 uint8_t *o_buf, uint8_t is_init)
{
	elink_status_t rc = ELINK_STATUS_OK;
	uint8_t i, j = 0, cnt = 0;
	uint32_t data_array[4];
	uint16_t addr32;
	struct bxe_softc *sc = params->sc;

	if (byte_cnt > ELINK_SFP_EEPROM_PAGE_SIZE) {
		ELINK_DEBUG_P0(sc,
		   "Reading from eeprom is limited to 16 bytes\n");
		return ELINK_STATUS_ERROR;
	}

	/* 4 byte aligned address */
	addr32 = addr & (~0x3);
	do {
		if ((!is_init) && (cnt == I2C_WA_PWR_ITER)) {
			elink_warpcore_power_module(params, 0);
			/* Note that 100us are not enough here */
			DELAY(1000 * 1);
			elink_warpcore_power_module(params, 1);
		}

		elink_bsc_module_sel(params);
		rc = elink_bsc_read(sc, dev_addr, addr32, 0, byte_cnt,
				    data_array);
	} while ((rc != ELINK_STATUS_OK) && (++cnt < I2C_WA_RETRY_CNT));

	if (rc == ELINK_STATUS_OK) {
		for (i = (addr - addr32); i < byte_cnt + (addr - addr32); i++) {
			o_buf[j] = *((uint8_t *)data_array + i);
			j++;
		}
	}

	return rc;
}