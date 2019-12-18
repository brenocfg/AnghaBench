#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {int op_flags; int eepMisc; } ;
struct TYPE_6__ {int* reg_dmn; int txrx_mask; int rf_silent; int blue_tooth_options; int device_cap; int device_type; int pwrTableOffset; int* params_for_tuning_caps; int feature_enable; int misc_configuration; int eeprom_write_enable_gpio; int wlan_disable_gpio; int wlan_led_gpio; int rx_band_select_gpio; int txrxgain; int swreg; TYPE_1__ op_cap_flags; } ;
struct TYPE_5__ {TYPE_3__ base_eep_header; } ;
typedef  TYPE_2__ ar9300_eeprom_t ;
typedef  TYPE_3__ OSPREY_BASE_EEP_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,int,...) ; 

__attribute__((used)) static void
eeprom_9300_base_print(const uint16_t *buf)
{
	const ar9300_eeprom_t *ee = (ar9300_eeprom_t *) buf;
	const OSPREY_BASE_EEP_HEADER *ee_base = &ee->base_eep_header;

	printf("| RegDomain: 0x%02x 0x%02x TxRxMask: 0x%02x OpFlags: 0x%02x OpMisc: 0x%02x |\n",
	    ee_base->reg_dmn[0],
	    ee_base->reg_dmn[1],
	    ee_base->txrx_mask,
	    ee_base->op_cap_flags.op_flags,
	    ee_base->op_cap_flags.eepMisc);

	printf("| RfSilent: 0x%02x BtOptions: 0x%02x DeviceCap: 0x%02x DeviceType: 0x%02x |\n",
	    ee_base->rf_silent,
	    ee_base->blue_tooth_options,
	    ee_base->device_cap,
	    ee_base->device_type);

	printf("| pwrTableOffset: %d dB, TuningCaps=0x%02x 0x%02x feature_enable: 0x%02x MiscConfig: 0x%02x |\n",
	    ee_base->pwrTableOffset,
	    ee_base->params_for_tuning_caps[0],
	    ee_base->params_for_tuning_caps[1],
	    ee_base->feature_enable,
	    ee_base->misc_configuration);

	printf("| EepromWriteGpio: %d, WlanDisableGpio: %d, WlanLedGpio: %d RxBandSelectGpio: %d |\n",
	    ee_base->eeprom_write_enable_gpio,
	    ee_base->wlan_disable_gpio,
	    ee_base->wlan_led_gpio,
	    ee_base->rx_band_select_gpio);

	printf("| TxRxGain: %d, SwReg: %d |\n",
	    ee_base->txrxgain,
	    ee_base->swreg);
}