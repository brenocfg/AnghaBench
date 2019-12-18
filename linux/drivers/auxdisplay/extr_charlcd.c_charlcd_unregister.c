#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* ops; } ;
struct charlcd_priv {TYPE_3__ lcd; int /*<<< orphan*/  bl_work; } ;
struct charlcd {TYPE_1__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* backlight ) (TYPE_3__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {scalar_t__ backlight; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  charlcd_dev ; 
 int /*<<< orphan*/  charlcd_puts (struct charlcd*,char*) ; 
 struct charlcd_priv* charlcd_to_priv (struct charlcd*) ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panel_notifier ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * the_charlcd ; 
 int /*<<< orphan*/  unregister_reboot_notifier (int /*<<< orphan*/ *) ; 

int charlcd_unregister(struct charlcd *lcd)
{
	struct charlcd_priv *priv = charlcd_to_priv(lcd);

	unregister_reboot_notifier(&panel_notifier);
	charlcd_puts(lcd, "\x0cLCD driver unloaded.\x1b[Lc\x1b[Lb\x1b[L-");
	misc_deregister(&charlcd_dev);
	the_charlcd = NULL;
	if (lcd->ops->backlight) {
		cancel_delayed_work_sync(&priv->bl_work);
		priv->lcd.ops->backlight(&priv->lcd, 0);
	}

	return 0;
}