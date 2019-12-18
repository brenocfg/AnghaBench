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
typedef  int u16 ;
struct adm6996_priv {int /*<<< orphan*/  eedi; int /*<<< orphan*/  eesk; int /*<<< orphan*/  eecs; } ;
typedef  enum admreg { ____Placeholder_admreg } admreg ;

/* Variables and functions */
 int /*<<< orphan*/  adm6996_gpio_adclk (struct adm6996_priv*,int) ; 
 int /*<<< orphan*/  adm6996_gpio_write (struct adm6996_priv*,int,int*,int) ; 
 int /*<<< orphan*/  gpio_direction_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
adm6996_write_gpio_reg(struct adm6996_priv *priv, enum admreg reg, u16 val)
{
	/* cmd(27bits): sb(1) + opc(01) + addr(bbbbbbbb) + data(bbbbbbbbbbbbbbbb) */
	u8 bits[4] = {
		(0x05 << 5) | (reg >> 3),
		(reg << 5) | (u8)(val >> 11),
		(u8)(val >> 3),
		(u8)(val << 5)
	};

	/* Enable GPIO outputs with all pins to 0 */
	gpio_direction_output(priv->eecs, 0);
	gpio_direction_output(priv->eesk, 0);
	gpio_direction_output(priv->eedi, 0);

	/* Write cmd. Total 27 bits */
	adm6996_gpio_write(priv, 1, bits, 27);

	/* Extra clock(s) required per datasheet */
	adm6996_gpio_adclk(priv, 2);

	/* Disable GPIO outputs */
	gpio_direction_input(priv->eecs);
	gpio_direction_input(priv->eesk);
	gpio_direction_input(priv->eedi);
}