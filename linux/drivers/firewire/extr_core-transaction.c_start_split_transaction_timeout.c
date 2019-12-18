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
struct fw_transaction {int is_split_transaction; int /*<<< orphan*/  split_timeout_timer; int /*<<< orphan*/  link; } ;
struct fw_card {int /*<<< orphan*/  lock; scalar_t__ split_timeout_jiffies; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ jiffies ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void start_split_transaction_timeout(struct fw_transaction *t,
					    struct fw_card *card)
{
	unsigned long flags;

	spin_lock_irqsave(&card->lock, flags);

	if (list_empty(&t->link) || WARN_ON(t->is_split_transaction)) {
		spin_unlock_irqrestore(&card->lock, flags);
		return;
	}

	t->is_split_transaction = true;
	mod_timer(&t->split_timeout_timer,
		  jiffies + card->split_timeout_jiffies);

	spin_unlock_irqrestore(&card->lock, flags);
}