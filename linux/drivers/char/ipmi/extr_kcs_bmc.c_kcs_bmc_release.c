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
struct kcs_bmc {int /*<<< orphan*/  lock; scalar_t__ running; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kcs_force_abort (struct kcs_bmc*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct kcs_bmc* to_kcs_bmc (struct file*) ; 

__attribute__((used)) static int kcs_bmc_release(struct inode *inode, struct file *filp)
{
	struct kcs_bmc *kcs_bmc = to_kcs_bmc(filp);

	spin_lock_irq(&kcs_bmc->lock);
	kcs_bmc->running = 0;
	kcs_force_abort(kcs_bmc);
	spin_unlock_irq(&kcs_bmc->lock);

	return 0;
}