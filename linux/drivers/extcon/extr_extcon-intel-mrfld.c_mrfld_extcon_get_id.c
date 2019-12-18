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
struct regmap {int dummy; } ;
struct mrfld_extcon_data {int /*<<< orphan*/  id; struct regmap* regmap; } ;

/* Variables and functions */
 char BCOVE_MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCOVE_USBIDSTS ; 
 unsigned int BCOVE_USBIDSTS_FLOAT ; 
 unsigned int BCOVE_USBIDSTS_GND ; 
 unsigned int BCOVE_USBIDSTS_RARBRC_MASK ; 
 unsigned int BCOVE_USBIDSTS_RARBRC_SHIFT ; 
#define  BCOVE_USBIDSTS_R_ID_A 130 
#define  BCOVE_USBIDSTS_R_ID_B 129 
#define  BCOVE_USBIDSTS_R_ID_C 128 
 int INTEL_USB_ID_FLOAT ; 
 int INTEL_USB_ID_GND ; 
 int INTEL_USB_RID_A ; 
 int INTEL_USB_RID_B ; 
 int INTEL_USB_RID_C ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int mrfld_extcon_get_id(struct mrfld_extcon_data *data)
{
	struct regmap *regmap = data->regmap;
	unsigned int id;
	bool ground;
	int ret;

	ret = regmap_read(regmap, BCOVE_USBIDSTS, &id);
	if (ret)
		return ret;

	if (id & BCOVE_USBIDSTS_FLOAT)
		return INTEL_USB_ID_FLOAT;

	switch ((id & BCOVE_USBIDSTS_RARBRC_MASK) >> BCOVE_USBIDSTS_RARBRC_SHIFT) {
	case BCOVE_USBIDSTS_R_ID_A:
		return INTEL_USB_RID_A;
	case BCOVE_USBIDSTS_R_ID_B:
		return INTEL_USB_RID_B;
	case BCOVE_USBIDSTS_R_ID_C:
		return INTEL_USB_RID_C;
	}

	/*
	 * PMIC A0 reports USBIDSTS_GND = 1 for ID_GND,
	 * but PMIC B0 reports USBIDSTS_GND = 0 for ID_GND.
	 * Thus we must check this bit at last.
	 */
	ground = id & BCOVE_USBIDSTS_GND;
	switch ('A' + BCOVE_MAJOR(data->id)) {
	case 'A':
		return ground ? INTEL_USB_ID_GND : INTEL_USB_ID_FLOAT;
	case 'B':
		return ground ? INTEL_USB_ID_FLOAT : INTEL_USB_ID_GND;
	}

	/* Unknown or unsupported type */
	return INTEL_USB_ID_FLOAT;
}