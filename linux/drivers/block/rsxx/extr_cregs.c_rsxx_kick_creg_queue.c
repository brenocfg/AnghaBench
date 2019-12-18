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
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; } ;
struct rsxx_cardinfo {TYPE_1__ creg_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  creg_kick_queue (struct rsxx_cardinfo*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void rsxx_kick_creg_queue(struct rsxx_cardinfo *card)
{
	spin_lock_bh(&card->creg_ctrl.lock);
	if (!list_empty(&card->creg_ctrl.queue))
		creg_kick_queue(card);
	spin_unlock_bh(&card->creg_ctrl.lock);
}