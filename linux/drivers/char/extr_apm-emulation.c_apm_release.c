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
struct inode {int dummy; } ;
struct file {struct apm_user* private_data; } ;
struct apm_user {scalar_t__ suspend_state; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 scalar_t__ SUSPEND_PENDING ; 
 scalar_t__ SUSPEND_READ ; 
 int /*<<< orphan*/  apm_suspend_waitqueue ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct apm_user*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  state_lock ; 
 int /*<<< orphan*/  suspend_acks_pending ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_list_lock ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int apm_release(struct inode * inode, struct file * filp)
{
	struct apm_user *as = filp->private_data;

	filp->private_data = NULL;

	down_write(&user_list_lock);
	list_del(&as->list);
	up_write(&user_list_lock);

	/*
	 * We are now unhooked from the chain.  As far as new
	 * events are concerned, we no longer exist.
	 */
	mutex_lock(&state_lock);
	if (as->suspend_state == SUSPEND_PENDING ||
	    as->suspend_state == SUSPEND_READ)
		atomic_dec(&suspend_acks_pending);
	mutex_unlock(&state_lock);

	wake_up(&apm_suspend_waitqueue);

	kfree(as);
	return 0;
}