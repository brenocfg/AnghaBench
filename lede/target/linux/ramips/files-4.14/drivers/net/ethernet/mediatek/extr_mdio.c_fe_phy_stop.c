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
struct fe_priv {TYPE_2__* phy; TYPE_1__* soc; scalar_t__* link; } ;
struct TYPE_4__ {scalar_t__* phy; int /*<<< orphan*/  lock; scalar_t__* phy_fixed; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* mdio_adjust_link ) (struct fe_priv*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  phy_stop (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct fe_priv*,int) ; 

__attribute__((used)) static void fe_phy_stop(struct fe_priv *priv)
{
	unsigned long flags;
	int i;

	for (i = 0; i < 8; i++)
		if (priv->phy->phy_fixed[i]) {
			spin_lock_irqsave(&priv->phy->lock, flags);
			priv->link[i] = 0;
			if (priv->soc->mdio_adjust_link)
				priv->soc->mdio_adjust_link(priv, i);
			spin_unlock_irqrestore(&priv->phy->lock, flags);
		} else if (priv->phy->phy[i]) {
			phy_stop(priv->phy->phy[i]);
		}
}