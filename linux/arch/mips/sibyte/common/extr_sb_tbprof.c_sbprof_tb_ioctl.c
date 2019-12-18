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
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tb_read; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SBPROF_ZBSTART 130 
#define  SBPROF_ZBSTOP 129 
#define  SBPROF_ZBWAITFULL 128 
 int /*<<< orphan*/  TB_FULL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int put_user (int /*<<< orphan*/ ,int*) ; 
 TYPE_1__ sbp ; 
 int sbprof_zbprof_start (struct file*) ; 
 int sbprof_zbprof_stop () ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long sbprof_tb_ioctl(struct file *filp,
			    unsigned int command,
			    unsigned long arg)
{
	int err = 0;

	switch (command) {
	case SBPROF_ZBSTART:
		mutex_lock(&sbp.lock);
		err = sbprof_zbprof_start(filp);
		mutex_unlock(&sbp.lock);
		break;

	case SBPROF_ZBSTOP:
		mutex_lock(&sbp.lock);
		err = sbprof_zbprof_stop();
		mutex_unlock(&sbp.lock);
		break;

	case SBPROF_ZBWAITFULL: {
		err = wait_event_interruptible(sbp.tb_read, TB_FULL);
		if (err)
			break;

		err = put_user(TB_FULL, (int *) arg);
		break;
	}

	default:
		err = -EINVAL;
		break;
	}

	return err;
}