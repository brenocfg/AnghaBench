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
struct ccp_device {int sb_avail; int /*<<< orphan*/  sb_queue; int /*<<< orphan*/  sb_mutex; int /*<<< orphan*/  sb; } ;
struct ccp_cmd_queue {struct ccp_device* ccp; } ;

/* Variables and functions */
 scalar_t__ KSB_START ; 
 int /*<<< orphan*/  bitmap_clear (int /*<<< orphan*/ ,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ccp_free_ksb(struct ccp_cmd_queue *cmd_q, unsigned int start,
			 unsigned int count)
{
	struct ccp_device *ccp = cmd_q->ccp;

	if (!start)
		return;

	mutex_lock(&ccp->sb_mutex);

	bitmap_clear(ccp->sb, start - KSB_START, count);

	ccp->sb_avail = 1;

	mutex_unlock(&ccp->sb_mutex);

	wake_up_interruptible_all(&ccp->sb_queue);
}