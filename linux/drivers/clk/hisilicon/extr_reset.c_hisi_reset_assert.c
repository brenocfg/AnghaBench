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
typedef  unsigned long u8 ;
typedef  int u32 ;
struct reset_controller_dev {int dummy; } ;
struct hisi_reset_controller {int /*<<< orphan*/  lock; scalar_t__ membase; } ;

/* Variables and functions */
 int BIT (unsigned long) ; 
 unsigned long HISI_RESET_BIT_MASK ; 
 unsigned long HISI_RESET_OFFSET_MASK ; 
 unsigned long HISI_RESET_OFFSET_SHIFT ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct hisi_reset_controller* to_hisi_reset_controller (struct reset_controller_dev*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int hisi_reset_assert(struct reset_controller_dev *rcdev,
			      unsigned long id)
{
	struct hisi_reset_controller *rstc = to_hisi_reset_controller(rcdev);
	unsigned long flags;
	u32 offset, reg;
	u8 bit;

	offset = (id & HISI_RESET_OFFSET_MASK) >> HISI_RESET_OFFSET_SHIFT;
	bit = id & HISI_RESET_BIT_MASK;

	spin_lock_irqsave(&rstc->lock, flags);

	reg = readl(rstc->membase + offset);
	writel(reg | BIT(bit), rstc->membase + offset);

	spin_unlock_irqrestore(&rstc->lock, flags);

	return 0;
}