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
struct max8997_muic_info {int* status; int /*<<< orphan*/  dev; int /*<<< orphan*/  edev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  EXTCON_CHG_USB_CDP ; 
 int /*<<< orphan*/  EXTCON_CHG_USB_DCP ; 
 int /*<<< orphan*/  EXTCON_CHG_USB_FAST ; 
 int /*<<< orphan*/  EXTCON_CHG_USB_SLOW ; 
 int /*<<< orphan*/  MAX8997_CABLE_GROUP_CHG ; 
#define  MAX8997_CHARGER_TYPE_1A 133 
#define  MAX8997_CHARGER_TYPE_500MA 132 
#define  MAX8997_CHARGER_TYPE_DEDICATED_CHG 131 
#define  MAX8997_CHARGER_TYPE_DOWNSTREAM_PORT 130 
#define  MAX8997_CHARGER_TYPE_NONE 129 
#define  MAX8997_CHARGER_TYPE_USB 128 
 int MAX8997_MUIC_ADC_OPEN ; 
 int /*<<< orphan*/  MAX8997_USB_DEVICE ; 
 int STATUS1_ADC_MASK ; 
 int STATUS1_ADC_SHIFT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  extcon_set_state_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int max8997_muic_get_cable_type (struct max8997_muic_info*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  max8997_muic_handle_usb (struct max8997_muic_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int max8997_muic_chg_handler(struct max8997_muic_info *info)
{
	int chg_type;
	bool attached;
	int adc;

	chg_type = max8997_muic_get_cable_type(info,
				MAX8997_CABLE_GROUP_CHG, &attached);

	switch (chg_type) {
	case MAX8997_CHARGER_TYPE_NONE:
		break;
	case MAX8997_CHARGER_TYPE_USB:
		adc = info->status[0] & STATUS1_ADC_MASK;
		adc >>= STATUS1_ADC_SHIFT;

		if ((adc & STATUS1_ADC_MASK) == MAX8997_MUIC_ADC_OPEN) {
			max8997_muic_handle_usb(info,
					MAX8997_USB_DEVICE, attached);
		}
		break;
	case MAX8997_CHARGER_TYPE_DOWNSTREAM_PORT:
		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_CDP,
					attached);
		break;
	case MAX8997_CHARGER_TYPE_DEDICATED_CHG:
		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_DCP,
					attached);
		break;
	case MAX8997_CHARGER_TYPE_500MA:
		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_SLOW,
					attached);
		break;
	case MAX8997_CHARGER_TYPE_1A:
		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_FAST,
					attached);
		break;
	default:
		dev_err(info->dev,
			"failed to detect %s unknown chg cable (type:0x%x)\n",
			attached ? "attached" : "detached", chg_type);
		return -EINVAL;
	}

	return 0;
}