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
struct he_irq {int dummy; } ;
struct he_dev {int* irq_tailoffset; int /*<<< orphan*/  global_lock; int /*<<< orphan*/  tasklet; struct he_irq* irq_tail; struct he_irq* irq_head; scalar_t__ irq_base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  HPRINTK (char*) ; 
 int /*<<< orphan*/  INT_CLEAR_A ; 
 int /*<<< orphan*/  INT_FIFO ; 
 int /*<<< orphan*/  IRQ0_BASE ; 
 int IRQ_MASK ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int he_readl (struct he_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  he_writel (struct he_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hprintk (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t
he_irq_handler(int irq, void *dev_id)
{
	unsigned long flags;
	struct he_dev *he_dev = (struct he_dev * )dev_id;
	int handled = 0;

	if (he_dev == NULL)
		return IRQ_NONE;

	spin_lock_irqsave(&he_dev->global_lock, flags);

	he_dev->irq_tail = (struct he_irq *) (((unsigned long)he_dev->irq_base) |
						(*he_dev->irq_tailoffset << 2));

	if (he_dev->irq_tail == he_dev->irq_head) {
		HPRINTK("tailoffset not updated?\n");
		he_dev->irq_tail = (struct he_irq *) ((unsigned long)he_dev->irq_base |
			((he_readl(he_dev, IRQ0_BASE) & IRQ_MASK) << 2));
		(void) he_readl(he_dev, INT_FIFO);	/* 8.1.2 controller errata */
	}

#ifdef DEBUG
	if (he_dev->irq_head == he_dev->irq_tail /* && !IRQ_PENDING */)
		hprintk("spurious (or shared) interrupt?\n");
#endif

	if (he_dev->irq_head != he_dev->irq_tail) {
		handled = 1;
		tasklet_schedule(&he_dev->tasklet);
		he_writel(he_dev, INT_CLEAR_A, INT_FIFO);	/* clear interrupt */
		(void) he_readl(he_dev, INT_FIFO);		/* flush posted writes */
	}
	spin_unlock_irqrestore(&he_dev->global_lock, flags);
	return IRQ_RETVAL(handled);

}