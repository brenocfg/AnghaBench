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
struct TYPE_4__ {scalar_t__ y; scalar_t__ x; } ;
struct charlcd_priv {TYPE_2__ addr; } ;
struct charlcd {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* write_cmd ) (struct charlcd*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LCD_CMD_DISPLAY_CLEAR ; 
 struct charlcd_priv* charlcd_to_priv (struct charlcd*) ; 
 int /*<<< orphan*/  long_sleep (int) ; 
 int /*<<< orphan*/  stub1 (struct charlcd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void charlcd_clear_display(struct charlcd *lcd)
{
	struct charlcd_priv *priv = charlcd_to_priv(lcd);

	lcd->ops->write_cmd(lcd, LCD_CMD_DISPLAY_CLEAR);
	priv->addr.x = 0;
	priv->addr.y = 0;
	/* we must wait a few milliseconds (15) */
	long_sleep(15);
}