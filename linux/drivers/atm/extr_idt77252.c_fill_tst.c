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
struct vc_map {int dummy; } ;
struct idt77252_dev {int /*<<< orphan*/  tst_lock; int /*<<< orphan*/  tst_timer; int /*<<< orphan*/  tst_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  TST_SWITCH_PENDING ; 
 int __fill_tst (struct idt77252_dev*,struct vc_map*,int,unsigned int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
fill_tst(struct idt77252_dev *card, struct vc_map *vc, int n, unsigned int opc)
{
	unsigned long flags;
	int res;

	spin_lock_irqsave(&card->tst_lock, flags);

	res = __fill_tst(card, vc, n, opc);

	set_bit(TST_SWITCH_PENDING, &card->tst_state);
	if (!timer_pending(&card->tst_timer))
		mod_timer(&card->tst_timer, jiffies + 1);

	spin_unlock_irqrestore(&card->tst_lock, flags);
	return res;
}