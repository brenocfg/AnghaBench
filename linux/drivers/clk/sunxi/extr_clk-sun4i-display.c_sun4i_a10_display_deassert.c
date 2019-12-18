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
typedef  int u32 ;
struct reset_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  reg; scalar_t__ offset; } ;
struct reset_controller_dev {int dummy; } ;

/* Variables and functions */
 int BIT (scalar_t__) ; 
 struct reset_data* rcdev_to_reset_data (struct reset_controller_dev*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sun4i_a10_display_deassert(struct reset_controller_dev *rcdev,
				      unsigned long id)
{
	struct reset_data *data = rcdev_to_reset_data(rcdev);
	unsigned long flags;
	u32 reg;

	spin_lock_irqsave(data->lock, flags);

	reg = readl(data->reg);
	writel(reg | BIT(data->offset + id), data->reg);

	spin_unlock_irqrestore(data->lock, flags);

	return 0;
}