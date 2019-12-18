#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct gen_74x164_chip {int /*<<< orphan*/  registers; int /*<<< orphan*/  buffer; TYPE_1__ gpio_chip; } ;

/* Variables and functions */
 int spi_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_spi_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __gen_74x164_write_config(struct gen_74x164_chip *chip)
{
	return spi_write(to_spi_device(chip->gpio_chip.parent), chip->buffer,
			 chip->registers);
}