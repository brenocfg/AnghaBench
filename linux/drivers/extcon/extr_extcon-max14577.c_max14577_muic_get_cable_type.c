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
struct max14577_muic_info {int* status; int prev_cable_type; int prev_chg_type; int /*<<< orphan*/  dev; } ;
typedef  enum max14577_muic_cable_group { ____Placeholder_max14577_muic_cable_group } max14577_muic_cable_group ;

/* Variables and functions */
 int EINVAL ; 
#define  MAX14577_CABLE_GROUP_ADC 129 
#define  MAX14577_CABLE_GROUP_CHG 128 
 int MAX14577_CHARGER_TYPE_NONE ; 
 int MAX14577_MUIC_ADC_OPEN ; 
 size_t MAX14577_MUIC_STATUS1 ; 
 size_t MAX14577_MUIC_STATUS2 ; 
 int STATUS1_ADC_MASK ; 
 int STATUS1_ADC_SHIFT ; 
 int STATUS2_CHGTYP_MASK ; 
 int STATUS2_CHGTYP_SHIFT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int max14577_muic_get_cable_type(struct max14577_muic_info *info,
		enum max14577_muic_cable_group group, bool *attached)
{
	int cable_type = 0;
	int adc;
	int chg_type;

	switch (group) {
	case MAX14577_CABLE_GROUP_ADC:
		/*
		 * Read ADC value to check cable type and decide cable state
		 * according to cable type
		 */
		adc = info->status[MAX14577_MUIC_STATUS1] & STATUS1_ADC_MASK;
		adc >>= STATUS1_ADC_SHIFT;

		/*
		 * Check current cable state/cable type and store cable type
		 * (info->prev_cable_type) for handling cable when cable is
		 * detached.
		 */
		if (adc == MAX14577_MUIC_ADC_OPEN) {
			*attached = false;

			cable_type = info->prev_cable_type;
			info->prev_cable_type = MAX14577_MUIC_ADC_OPEN;
		} else {
			*attached = true;

			cable_type = info->prev_cable_type = adc;
		}
		break;
	case MAX14577_CABLE_GROUP_CHG:
		/*
		 * Read charger type to check cable type and decide cable state
		 * according to type of charger cable.
		 */
		chg_type = info->status[MAX14577_MUIC_STATUS2] &
			STATUS2_CHGTYP_MASK;
		chg_type >>= STATUS2_CHGTYP_SHIFT;

		if (chg_type == MAX14577_CHARGER_TYPE_NONE) {
			*attached = false;

			cable_type = info->prev_chg_type;
			info->prev_chg_type = MAX14577_CHARGER_TYPE_NONE;
		} else {
			*attached = true;

			/*
			 * Check current cable state/cable type and store cable
			 * type(info->prev_chg_type) for handling cable when
			 * charger cable is detached.
			 */
			cable_type = info->prev_chg_type = chg_type;
		}

		break;
	default:
		dev_err(info->dev, "Unknown cable group (%d)\n", group);
		cable_type = -EINVAL;
		break;
	}

	return cable_type;
}