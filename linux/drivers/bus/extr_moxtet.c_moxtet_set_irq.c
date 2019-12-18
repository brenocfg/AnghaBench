#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct moxtet_irqpos {int idx; int bit; } ;
struct TYPE_3__ {int /*<<< orphan*/  exists; struct moxtet_irqpos* position; } ;
struct moxtet {TYPE_1__ irq; } ;
struct TYPE_4__ {int hwirq_base; int nirqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int EINVAL ; 
 int MOXTET_NIRQS ; 
 TYPE_2__* mox_module_table ; 

__attribute__((used)) static int moxtet_set_irq(struct moxtet *moxtet, int idx, int id, int nsame)
{
	int i, first;
	struct moxtet_irqpos *pos;

	first = mox_module_table[id].hwirq_base +
		nsame * mox_module_table[id].nirqs;

	if (first + mox_module_table[id].nirqs > MOXTET_NIRQS)
		return -EINVAL;

	for (i = 0; i < mox_module_table[id].nirqs; ++i) {
		pos = &moxtet->irq.position[first + i];
		pos->idx = idx;
		pos->bit = i;
		moxtet->irq.exists |= BIT(first + i);
	}

	return 0;
}