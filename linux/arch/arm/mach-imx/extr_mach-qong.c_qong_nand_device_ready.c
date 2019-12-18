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
struct nand_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOMUX_TO_GPIO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MX31_PIN_NFRB ; 
 int gpio_get_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qong_nand_device_ready(struct nand_chip *chip)
{
	return gpio_get_value(IOMUX_TO_GPIO(MX31_PIN_NFRB));
}