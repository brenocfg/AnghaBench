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
struct diag210 {int dummy; } ;
struct TYPE_2__ {int (* diag210 ) (struct diag210*) ;} ;
typedef  int /*<<< orphan*/  DEFINE_SPINLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  DIAG_STAT_X210 ; 
 struct diag210* __diag210_tmp_dma ; 
 TYPE_1__ diag_dma_ops ; 
 int /*<<< orphan*/  diag_stat_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct diag210*) ; 

int diag210(struct diag210 *addr)
{
	static DEFINE_SPINLOCK(diag210_lock);
	unsigned long flags;
	int ccode;

	spin_lock_irqsave(&diag210_lock, flags);
	*__diag210_tmp_dma = *addr;

	diag_stat_inc(DIAG_STAT_X210);
	ccode = diag_dma_ops.diag210(__diag210_tmp_dma);

	*addr = *__diag210_tmp_dma;
	spin_unlock_irqrestore(&diag210_lock, flags);

	return ccode;
}