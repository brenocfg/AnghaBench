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
struct sahara_dev {int /*<<< orphan*/  dma_completion; int /*<<< orphan*/  error; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int SAHARA_CMD_CLEAR_ERR ; 
 int SAHARA_CMD_CLEAR_INT ; 
 int /*<<< orphan*/  SAHARA_REG_CMD ; 
 int /*<<< orphan*/  SAHARA_REG_ERRSTATUS ; 
 int /*<<< orphan*/  SAHARA_REG_STATUS ; 
 scalar_t__ SAHARA_STATE_BUSY ; 
 scalar_t__ SAHARA_STATE_COMPLETE ; 
 scalar_t__ SAHARA_STATUS_GET_STATE (unsigned int) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sahara_decode_error (struct sahara_dev*,unsigned int) ; 
 int /*<<< orphan*/  sahara_decode_status (struct sahara_dev*,unsigned int) ; 
 unsigned int sahara_read (struct sahara_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sahara_write (struct sahara_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t sahara_irq_handler(int irq, void *data)
{
	struct sahara_dev *dev = (struct sahara_dev *)data;
	unsigned int stat = sahara_read(dev, SAHARA_REG_STATUS);
	unsigned int err = sahara_read(dev, SAHARA_REG_ERRSTATUS);

	sahara_write(dev, SAHARA_CMD_CLEAR_INT | SAHARA_CMD_CLEAR_ERR,
		     SAHARA_REG_CMD);

	sahara_decode_status(dev, stat);

	if (SAHARA_STATUS_GET_STATE(stat) == SAHARA_STATE_BUSY) {
		return IRQ_NONE;
	} else if (SAHARA_STATUS_GET_STATE(stat) == SAHARA_STATE_COMPLETE) {
		dev->error = 0;
	} else {
		sahara_decode_error(dev, err);
		dev->error = -EINVAL;
	}

	complete(&dev->dma_completion);

	return IRQ_HANDLED;
}