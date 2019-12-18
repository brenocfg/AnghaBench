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
struct blk_mq_hw_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_MFP_FDC ; 
 int /*<<< orphan*/  ataflop_lock ; 
 int /*<<< orphan*/  atari_disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atari_enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_fdc () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ataflop_commit_rqs(struct blk_mq_hw_ctx *hctx)
{
	spin_lock_irq(&ataflop_lock);
	atari_disable_irq(IRQ_MFP_FDC);
	finish_fdc();
	atari_enable_irq(IRQ_MFP_FDC);
	spin_unlock_irq(&ataflop_lock);
}