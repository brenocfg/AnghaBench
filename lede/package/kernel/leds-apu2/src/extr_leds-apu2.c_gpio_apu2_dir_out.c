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
typedef  int /*<<< orphan*/  u32 ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_BIT_DIR ; 
 int /*<<< orphan*/ * gpio_addr ; 
 int /*<<< orphan*/  gpio_lock ; 
 int /*<<< orphan*/  ioread32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gpio_apu2_dir_out (struct gpio_chip *chip, unsigned offset,
		int value)
{
	u32 val;

	spin_lock_bh (&gpio_lock);

	val = ioread32 (gpio_addr[offset]);
	val |= BIT(GPIO_BIT_DIR);
	iowrite32 (val, gpio_addr[offset]);

	spin_unlock_bh (&gpio_lock);

	return 0;
}