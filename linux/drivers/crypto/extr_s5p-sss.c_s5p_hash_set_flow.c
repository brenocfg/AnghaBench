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
typedef  int /*<<< orphan*/  u32 ;
struct s5p_aes_dev {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCFIFOCTRL ; 
 int /*<<< orphan*/  SSS_HASHIN_MASK ; 
 int /*<<< orphan*/  SSS_READ (struct s5p_aes_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSS_WRITE (struct s5p_aes_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void s5p_hash_set_flow(struct s5p_aes_dev *dev, u32 hashflow)
{
	unsigned long flags;
	u32 flow;

	spin_lock_irqsave(&dev->lock, flags);

	flow = SSS_READ(dev, FCFIFOCTRL);
	flow &= ~SSS_HASHIN_MASK;
	flow |= hashflow;
	SSS_WRITE(dev, FCFIFOCTRL, flow);

	spin_unlock_irqrestore(&dev->lock, flags);
}