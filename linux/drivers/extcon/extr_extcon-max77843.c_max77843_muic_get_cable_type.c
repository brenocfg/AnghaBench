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
struct max77843_muic_info {int* status; int prev_cable_type; int prev_chg_type; int prev_gnd_type; int /*<<< orphan*/  dev; } ;
typedef  enum max77843_muic_cable_group { ____Placeholder_max77843_muic_cable_group } max77843_muic_cable_group ;

/* Variables and functions */
 int EINVAL ; 
#define  MAX77843_CABLE_GROUP_ADC 130 
#define  MAX77843_CABLE_GROUP_ADC_GND 129 
#define  MAX77843_CABLE_GROUP_CHG 128 
 int MAX77843_MUIC_ADC_GROUND ; 
 int MAX77843_MUIC_ADC_OPEN ; 
 int MAX77843_MUIC_ADC_RESERVED_ACC_3 ; 
 void* MAX77843_MUIC_CHG_DOCK ; 
 void* MAX77843_MUIC_CHG_GND ; 
 int MAX77843_MUIC_CHG_NONE ; 
 int MAX77843_MUIC_GND_USB_HOST ; 
 size_t MAX77843_MUIC_STATUS1 ; 
 int MAX77843_MUIC_STATUS1_ADC1K_MASK ; 
 int MAX77843_MUIC_STATUS1_ADC_MASK ; 
 int MAX77843_MUIC_STATUS1_ADC_SHIFT ; 
 size_t MAX77843_MUIC_STATUS2 ; 
 int MAX77843_MUIC_STATUS2_CHGTYP_MASK ; 
 int MAX77843_MUIC_STATUS2_VBVOLT_MASK ; 
 int MAX77843_MUIC_STATUS2_VBVOLT_SHIFT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int max77843_muic_get_cable_type(struct max77843_muic_info *info,
		enum max77843_muic_cable_group group, bool *attached)
{
	int adc, chg_type, cable_type, gnd_type;

	adc = info->status[MAX77843_MUIC_STATUS1] &
			MAX77843_MUIC_STATUS1_ADC_MASK;
	adc >>= MAX77843_MUIC_STATUS1_ADC_SHIFT;

	switch (group) {
	case MAX77843_CABLE_GROUP_ADC:
		if (adc == MAX77843_MUIC_ADC_OPEN) {
			*attached = false;
			cable_type = info->prev_cable_type;
			info->prev_cable_type = MAX77843_MUIC_ADC_OPEN;
		} else {
			*attached = true;
			cable_type = info->prev_cable_type = adc;
		}
		break;
	case MAX77843_CABLE_GROUP_CHG:
		chg_type = info->status[MAX77843_MUIC_STATUS2] &
				MAX77843_MUIC_STATUS2_CHGTYP_MASK;

		/* Check GROUND accessory with charger cable */
		if (adc == MAX77843_MUIC_ADC_GROUND) {
			if (chg_type == MAX77843_MUIC_CHG_NONE) {
				/*
				 * The following state when charger cable is
				 * disconnected but the GROUND accessory still
				 * connected.
				 */
				*attached = false;
				cable_type = info->prev_chg_type;
				info->prev_chg_type = MAX77843_MUIC_CHG_NONE;
			} else {

				/*
				 * The following state when charger cable is
				 * connected on the GROUND accessory.
				 */
				*attached = true;
				cable_type = MAX77843_MUIC_CHG_GND;
				info->prev_chg_type = MAX77843_MUIC_CHG_GND;
			}
			break;
		}

		if (adc == MAX77843_MUIC_ADC_RESERVED_ACC_3) { /* SmartDock */
			if (chg_type == MAX77843_MUIC_CHG_NONE) {
				*attached = false;
				cable_type = info->prev_chg_type;
				info->prev_chg_type = MAX77843_MUIC_CHG_NONE;
			} else {
				*attached = true;
				cable_type = MAX77843_MUIC_CHG_DOCK;
				info->prev_chg_type = MAX77843_MUIC_CHG_DOCK;
			}
			break;
		}

		if (chg_type == MAX77843_MUIC_CHG_NONE) {
			*attached = false;
			cable_type = info->prev_chg_type;
			info->prev_chg_type = MAX77843_MUIC_CHG_NONE;
		} else {
			*attached = true;
			cable_type = info->prev_chg_type = chg_type;
		}
		break;
	case MAX77843_CABLE_GROUP_ADC_GND:
		if (adc == MAX77843_MUIC_ADC_OPEN) {
			*attached = false;
			cable_type = info->prev_gnd_type;
			info->prev_gnd_type = MAX77843_MUIC_ADC_OPEN;
		} else {
			*attached = true;

			/*
			 * Offset|ADC1K|VBVolt|
			 *    0x1|    0|     0| USB-HOST
			 *    0x1|    0|     1| USB-HOST with VB
			 *    0x1|    1|     0| MHL
			 *    0x1|    1|     1| MHL with VB
			 */
			/* Get ADC1K register bit */
			gnd_type = (info->status[MAX77843_MUIC_STATUS1] &
					MAX77843_MUIC_STATUS1_ADC1K_MASK);

			/* Get VBVolt register bit */
			gnd_type |= (info->status[MAX77843_MUIC_STATUS2] &
					MAX77843_MUIC_STATUS2_VBVOLT_MASK);
			gnd_type >>= MAX77843_MUIC_STATUS2_VBVOLT_SHIFT;

			/* Offset of GND cable */
			gnd_type |= MAX77843_MUIC_GND_USB_HOST;
			cable_type = info->prev_gnd_type = gnd_type;
		}
		break;
	default:
		dev_err(info->dev, "Unknown cable group (%d)\n", group);
		cable_type = -EINVAL;
		break;
	}

	return cable_type;
}