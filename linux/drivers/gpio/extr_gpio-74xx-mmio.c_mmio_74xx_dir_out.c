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
struct mmio_74xx_gpio_priv {int flags; } ;
struct gpio_chip {int /*<<< orphan*/  (* set ) (struct gpio_chip*,unsigned int,int) ;} ;

/* Variables and functions */
 int ENOTSUPP ; 
 int MMIO_74XX_DIR_OUT ; 
 struct mmio_74xx_gpio_priv* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  stub1 (struct gpio_chip*,unsigned int,int) ; 

__attribute__((used)) static int mmio_74xx_dir_out(struct gpio_chip *gc, unsigned int gpio, int val)
{
	struct mmio_74xx_gpio_priv *priv = gpiochip_get_data(gc);

	if (priv->flags & MMIO_74XX_DIR_OUT) {
		gc->set(gc, gpio, val);
		return 0;
	}

	return -ENOTSUPP;
}