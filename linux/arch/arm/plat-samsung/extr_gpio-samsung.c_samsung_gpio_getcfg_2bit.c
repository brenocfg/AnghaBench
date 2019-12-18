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
typedef  unsigned int u32 ;
struct samsung_gpio_chip {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 unsigned int S3C_GPIO_SPECIAL (unsigned int) ; 
 unsigned int __raw_readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int samsung_gpio_getcfg_2bit(struct samsung_gpio_chip *chip,
					     unsigned int off)
{
	u32 con;

	con = __raw_readl(chip->base);
	con >>= off * 2;
	con &= 3;

	/* this conversion works for IN and OUT as well as special mode */
	return S3C_GPIO_SPECIAL(con);
}