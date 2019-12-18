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
struct tps65217_chgconfig2_reg {int /*<<< orphan*/  voreg; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  TPS65217_CHGCONFIG2_REG ; 
 int /*<<< orphan*/  am335x_pmic_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  am335x_pmic_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
am335x_pmic_setvo(device_t dev, uint8_t vo)
{
	struct tps65217_chgconfig2_reg reg2;

	am335x_pmic_read(dev, TPS65217_CHGCONFIG2_REG, (uint8_t *)&reg2, 1);
	reg2.voreg = vo;
	am335x_pmic_write(dev, TPS65217_CHGCONFIG2_REG, (uint8_t *)&reg2, 1);
}