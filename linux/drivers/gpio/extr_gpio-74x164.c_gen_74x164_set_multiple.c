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
typedef  size_t u8 ;
struct gpio_chip {int dummy; } ;
struct gen_74x164_chip {int registers; size_t* buffer; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned int BITS_PER_BYTE ; 
 int /*<<< orphan*/  __gen_74x164_write_config (struct gen_74x164_chip*) ; 
 struct gen_74x164_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gen_74x164_set_multiple(struct gpio_chip *gc, unsigned long *mask,
				    unsigned long *bits)
{
	struct gen_74x164_chip *chip = gpiochip_get_data(gc);
	unsigned int i, idx, shift;
	u8 bank, bankmask;

	mutex_lock(&chip->lock);
	for (i = 0, bank = chip->registers - 1; i < chip->registers;
	     i++, bank--) {
		idx = i / sizeof(*mask);
		shift = i % sizeof(*mask) * BITS_PER_BYTE;
		bankmask = mask[idx] >> shift;
		if (!bankmask)
			continue;

		chip->buffer[bank] &= ~bankmask;
		chip->buffer[bank] |= bankmask & (bits[idx] >> shift);
	}
	__gen_74x164_write_config(chip);
	mutex_unlock(&chip->lock);
}