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
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USRGPIR ; 
 int fpga_read_reg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usrgpir_gpio_get(struct gpio_chip *chip, unsigned gpio)
{
	return !!(fpga_read_reg(USRGPIR) & (1 << gpio));
}