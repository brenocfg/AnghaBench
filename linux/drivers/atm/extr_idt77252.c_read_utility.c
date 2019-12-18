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
typedef  int u8 ;
struct idt77252_dev {int /*<<< orphan*/  cmd_lock; } ;

/* Variables and functions */
 scalar_t__ SAR_CMD_READ_UTILITY ; 
 int /*<<< orphan*/  SAR_REG_CMD ; 
 int /*<<< orphan*/  SAR_REG_DR0 ; 
 int /*<<< orphan*/  printk (char*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  waitfor_idle (struct idt77252_dev*) ; 
 int /*<<< orphan*/  writel (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8
read_utility(void *dev, unsigned long ubus_addr)
{
	struct idt77252_dev *card = dev;
	unsigned long flags;
	u8 value;

	if (!card) {
		printk("Error: No such device.\n");
		return -1;
	}

	spin_lock_irqsave(&card->cmd_lock, flags);
	writel(SAR_CMD_READ_UTILITY + ubus_addr, SAR_REG_CMD);
	waitfor_idle(card);
	value = readl(SAR_REG_DR0);
	spin_unlock_irqrestore(&card->cmd_lock, flags);
	return value;
}