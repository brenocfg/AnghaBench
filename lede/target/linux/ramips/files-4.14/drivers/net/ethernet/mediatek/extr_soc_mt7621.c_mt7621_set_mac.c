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
struct fe_priv {int /*<<< orphan*/  page_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GSW_REG_GDMA1_MAC_ADRH ; 
 int /*<<< orphan*/  GSW_REG_GDMA1_MAC_ADRL ; 
 int /*<<< orphan*/  fe_w32 (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void mt7621_set_mac(struct fe_priv *priv, unsigned char *mac)
{
	unsigned long flags;

	spin_lock_irqsave(&priv->page_lock, flags);
	fe_w32((mac[0] << 8) | mac[1], GSW_REG_GDMA1_MAC_ADRH);
	fe_w32((mac[2] << 24) | (mac[3] << 16) | (mac[4] << 8) | mac[5],
	       GSW_REG_GDMA1_MAC_ADRL);
	spin_unlock_irqrestore(&priv->page_lock, flags);
}