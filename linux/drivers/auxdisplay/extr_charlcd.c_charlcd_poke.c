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
struct charlcd_priv {int bl_tempo; int flags; int /*<<< orphan*/  bl_tempo_lock; int /*<<< orphan*/  bl_work; } ;
struct charlcd {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* backlight ) (struct charlcd*,int) ;} ;

/* Variables and functions */
 int HZ ; 
 int LCD_BL_TEMPO_PERIOD ; 
 int LCD_FLAG_L ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct charlcd_priv* charlcd_to_priv (struct charlcd*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (struct charlcd*,int) ; 

void charlcd_poke(struct charlcd *lcd)
{
	struct charlcd_priv *priv = charlcd_to_priv(lcd);

	if (!lcd->ops->backlight)
		return;

	cancel_delayed_work_sync(&priv->bl_work);

	mutex_lock(&priv->bl_tempo_lock);
	if (!priv->bl_tempo && !(priv->flags & LCD_FLAG_L))
		lcd->ops->backlight(lcd, 1);
	priv->bl_tempo = true;
	schedule_delayed_work(&priv->bl_work, LCD_BL_TEMPO_PERIOD * HZ);
	mutex_unlock(&priv->bl_tempo_lock);
}