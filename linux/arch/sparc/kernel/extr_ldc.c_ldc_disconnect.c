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
struct TYPE_2__ {scalar_t__ mode; int /*<<< orphan*/  rx_irq; int /*<<< orphan*/  tx_irq; } ;
struct ldc_channel {int flags; int /*<<< orphan*/  lock; TYPE_1__ cfg; int /*<<< orphan*/  id; int /*<<< orphan*/  hs_state; int /*<<< orphan*/  rx_num_entries; int /*<<< orphan*/  rx_ra; int /*<<< orphan*/  tx_num_entries; int /*<<< orphan*/  tx_ra; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int LDC_FLAG_ALLOCED_QUEUES ; 
 int LDC_FLAG_REGISTERED_IRQS ; 
 int LDC_FLAG_REGISTERED_QUEUES ; 
 int LDC_FLAG_RESET ; 
 int /*<<< orphan*/  LDC_HS_OPEN ; 
 scalar_t__ LDC_MODE_RAW ; 
 int /*<<< orphan*/  LDC_STATE_BOUND ; 
 int /*<<< orphan*/  LDC_STATE_INIT ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ldc_channel*) ; 
 int /*<<< orphan*/  ldc_set_state (struct ldc_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long sun4v_ldc_rx_qconf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long sun4v_ldc_tx_qconf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ldc_disconnect(struct ldc_channel *lp)
{
	unsigned long hv_err, flags;
	int err;

	if (lp->cfg.mode == LDC_MODE_RAW)
		return -EINVAL;

	if (!(lp->flags & LDC_FLAG_ALLOCED_QUEUES) ||
	    !(lp->flags & LDC_FLAG_REGISTERED_QUEUES))
		return -EINVAL;

	spin_lock_irqsave(&lp->lock, flags);

	err = -ENODEV;
	hv_err = sun4v_ldc_tx_qconf(lp->id, 0, 0);
	if (hv_err)
		goto out_err;

	hv_err = sun4v_ldc_tx_qconf(lp->id, lp->tx_ra, lp->tx_num_entries);
	if (hv_err)
		goto out_err;

	hv_err = sun4v_ldc_rx_qconf(lp->id, 0, 0);
	if (hv_err)
		goto out_err;

	hv_err = sun4v_ldc_rx_qconf(lp->id, lp->rx_ra, lp->rx_num_entries);
	if (hv_err)
		goto out_err;

	ldc_set_state(lp, LDC_STATE_BOUND);
	lp->hs_state = LDC_HS_OPEN;
	lp->flags |= LDC_FLAG_RESET;

	spin_unlock_irqrestore(&lp->lock, flags);

	return 0;

out_err:
	sun4v_ldc_tx_qconf(lp->id, 0, 0);
	sun4v_ldc_rx_qconf(lp->id, 0, 0);
	free_irq(lp->cfg.tx_irq, lp);
	free_irq(lp->cfg.rx_irq, lp);
	lp->flags &= ~(LDC_FLAG_REGISTERED_IRQS |
		       LDC_FLAG_REGISTERED_QUEUES);
	ldc_set_state(lp, LDC_STATE_INIT);

	spin_unlock_irqrestore(&lp->lock, flags);

	return err;
}