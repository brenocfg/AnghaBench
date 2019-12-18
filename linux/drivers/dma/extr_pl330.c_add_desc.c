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
struct list_head {int dummy; } ;
struct dma_pl330_desc {int /*<<< orphan*/  node; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  _init_desc (struct dma_pl330_desc*) ; 
 struct dma_pl330_desc* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int add_desc(struct list_head *pool, spinlock_t *lock,
		    gfp_t flg, int count)
{
	struct dma_pl330_desc *desc;
	unsigned long flags;
	int i;

	desc = kcalloc(count, sizeof(*desc), flg);
	if (!desc)
		return 0;

	spin_lock_irqsave(lock, flags);

	for (i = 0; i < count; i++) {
		_init_desc(&desc[i]);
		list_add_tail(&desc[i].node, pool);
	}

	spin_unlock_irqrestore(lock, flags);

	return count;
}