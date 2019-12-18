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
struct sun4i_dma_pchan {int /*<<< orphan*/ * vchan; } ;
struct sun4i_dma_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/  pchans_used; struct sun4i_dma_pchan* pchans; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void release_pchan(struct sun4i_dma_dev *priv,
			  struct sun4i_dma_pchan *pchan)
{
	unsigned long flags;
	int nr = pchan - priv->pchans;

	spin_lock_irqsave(&priv->lock, flags);

	pchan->vchan = NULL;
	clear_bit(nr, priv->pchans_used);

	spin_unlock_irqrestore(&priv->lock, flags);
}