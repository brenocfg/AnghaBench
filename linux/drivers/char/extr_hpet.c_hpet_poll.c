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
struct hpet_dev {unsigned long hd_irqdata; int /*<<< orphan*/  hd_waitqueue; int /*<<< orphan*/  hd_ireqfreq; } ;
struct file {struct hpet_dev* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 int /*<<< orphan*/  hpet_lock ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t hpet_poll(struct file *file, poll_table * wait)
{
	unsigned long v;
	struct hpet_dev *devp;

	devp = file->private_data;

	if (!devp->hd_ireqfreq)
		return 0;

	poll_wait(file, &devp->hd_waitqueue, wait);

	spin_lock_irq(&hpet_lock);
	v = devp->hd_irqdata;
	spin_unlock_irq(&hpet_lock);

	if (v != 0)
		return EPOLLIN | EPOLLRDNORM;

	return 0;
}