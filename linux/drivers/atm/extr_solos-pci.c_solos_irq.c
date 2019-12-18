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
struct solos_card {int /*<<< orphan*/  fw_wq; int /*<<< orphan*/  tlet; scalar_t__* atmdev; scalar_t__ config_regs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ IRQ_CLEAR ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t solos_irq(int irq, void *dev_id)
{
	struct solos_card *card = dev_id;
	int handled = 1;

	iowrite32(0, card->config_regs + IRQ_CLEAR);

	/* If we're up and running, just kick the tasklet to process TX/RX */
	if (card->atmdev[0])
		tasklet_schedule(&card->tlet);
	else
		wake_up(&card->fw_wq);

	return IRQ_RETVAL(handled);
}