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
typedef  enum ctrl_register { ____Placeholder_ctrl_register } ctrl_register ;

/* Variables and functions */
 int CRYSTALCOVE_GPIO_NUM ; 
 int CTRL_IN ; 
 int EOPNOTSUPP ; 
 int GPIO0P0CTLI ; 
 int GPIO0P0CTLO ; 
 int GPIO1P0CTLI ; 
 int GPIO1P0CTLO ; 
 int GPIOPANELCTL ; 

__attribute__((used)) static inline int to_reg(int gpio, enum ctrl_register reg_type)
{
	int reg;

	if (gpio >= CRYSTALCOVE_GPIO_NUM) {
		/*
		 * Virtual GPIO called from ACPI, for now we only support
		 * the panel ctl.
		 */
		switch (gpio) {
		case 0x5e:
			return GPIOPANELCTL;
		default:
			return -EOPNOTSUPP;
		}
	}

	if (reg_type == CTRL_IN) {
		if (gpio < 8)
			reg = GPIO0P0CTLI;
		else
			reg = GPIO1P0CTLI;
	} else {
		if (gpio < 8)
			reg = GPIO0P0CTLO;
		else
			reg = GPIO1P0CTLO;
	}

	return reg + gpio % 8;
}