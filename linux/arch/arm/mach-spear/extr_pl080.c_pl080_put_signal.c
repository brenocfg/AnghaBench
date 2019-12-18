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
struct pl08x_channel_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  busy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  lock ; 
 TYPE_1__* signals ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void pl080_put_signal(const struct pl08x_channel_data *cd, int signal)
{
	unsigned long flags;

	spin_lock_irqsave(&lock, flags);

	/* if signal is not used */
	if (!signals[signal].busy)
		BUG();

	signals[signal].busy--;

	spin_unlock_irqrestore(&lock, flags);
}