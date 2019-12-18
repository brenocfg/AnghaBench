#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int x; int y; } ;
struct charlcd_priv {TYPE_2__ addr; } ;
struct charlcd {int bwidth; int hwidth; TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* write_cmd ) (struct charlcd*,unsigned int) ;} ;

/* Variables and functions */
 unsigned int LCD_CMD_SET_DDRAM_ADDR ; 
 struct charlcd_priv* charlcd_to_priv (struct charlcd*) ; 
 int /*<<< orphan*/  stub1 (struct charlcd*,unsigned int) ; 

__attribute__((used)) static void charlcd_gotoxy(struct charlcd *lcd)
{
	struct charlcd_priv *priv = charlcd_to_priv(lcd);
	unsigned int addr;

	/*
	 * we force the cursor to stay at the end of the
	 * line if it wants to go farther
	 */
	addr = priv->addr.x < lcd->bwidth ? priv->addr.x & (lcd->hwidth - 1)
					  : lcd->bwidth - 1;
	if (priv->addr.y & 1)
		addr += lcd->hwidth;
	if (priv->addr.y & 2)
		addr += lcd->bwidth;
	lcd->ops->write_cmd(lcd, LCD_CMD_SET_DDRAM_ADDR | addr);
}