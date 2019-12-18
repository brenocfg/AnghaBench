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
typedef  int u8 ;
struct gpio_chip {int dummy; } ;
struct adnp {unsigned int reg_shift; int /*<<< orphan*/  i2c_lock; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int EPERM ; 
 scalar_t__ GPIO_DDR (struct adnp*) ; 
 int /*<<< orphan*/  __adnp_gpio_set (struct adnp*,unsigned int,int) ; 
 int adnp_read (struct adnp*,scalar_t__,int*) ; 
 int adnp_write (struct adnp*,scalar_t__,int) ; 
 struct adnp* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adnp_gpio_direction_output(struct gpio_chip *chip, unsigned offset,
				      int value)
{
	struct adnp *adnp = gpiochip_get_data(chip);
	unsigned int reg = offset >> adnp->reg_shift;
	unsigned int pos = offset & 7;
	int err;
	u8 val;

	mutex_lock(&adnp->i2c_lock);

	err = adnp_read(adnp, GPIO_DDR(adnp) + reg, &val);
	if (err < 0)
		goto out;

	val |= BIT(pos);

	err = adnp_write(adnp, GPIO_DDR(adnp) + reg, val);
	if (err < 0)
		goto out;

	err = adnp_read(adnp, GPIO_DDR(adnp) + reg, &val);
	if (err < 0)
		goto out;

	if (!(val & BIT(pos))) {
		err = -EPERM;
		goto out;
	}

	__adnp_gpio_set(adnp, offset, value);
	err = 0;

out:
	mutex_unlock(&adnp->i2c_lock);
	return err;
}