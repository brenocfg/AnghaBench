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
struct timer_group_priv {unsigned int idle; int /*<<< orphan*/  lock; struct mpic_timer* timer; } ;
struct mpic_timer {struct cascade_priv* cascade_handle; } ;
struct cascade_priv {unsigned int cascade_map; unsigned int timer_num; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct cascade_priv*) ; 
 struct cascade_priv* cascade_timer ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct mpic_timer *detect_idle_cascade_timer(
					struct timer_group_priv *priv)
{
	struct cascade_priv *casc_priv;
	unsigned int map;
	unsigned int array_size = ARRAY_SIZE(cascade_timer);
	unsigned int num;
	unsigned int i;
	unsigned long flags;

	casc_priv = cascade_timer;
	for (i = 0; i < array_size; i++) {
		spin_lock_irqsave(&priv->lock, flags);
		map = casc_priv->cascade_map & priv->idle;
		if (map == casc_priv->cascade_map) {
			num = casc_priv->timer_num;
			priv->timer[num].cascade_handle = casc_priv;

			/* set timer busy */
			priv->idle &= ~casc_priv->cascade_map;
			spin_unlock_irqrestore(&priv->lock, flags);
			return &priv->timer[num];
		}
		spin_unlock_irqrestore(&priv->lock, flags);
		casc_priv++;
	}

	return NULL;
}