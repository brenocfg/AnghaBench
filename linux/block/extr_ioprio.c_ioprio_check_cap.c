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

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EINVAL ; 
 int EPERM ; 
 int IOPRIO_BE_NR ; 
#define  IOPRIO_CLASS_BE 131 
#define  IOPRIO_CLASS_IDLE 130 
#define  IOPRIO_CLASS_NONE 129 
#define  IOPRIO_CLASS_RT 128 
 int IOPRIO_PRIO_CLASS (int) ; 
 int IOPRIO_PRIO_DATA (int) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 

int ioprio_check_cap(int ioprio)
{
	int class = IOPRIO_PRIO_CLASS(ioprio);
	int data = IOPRIO_PRIO_DATA(ioprio);

	switch (class) {
		case IOPRIO_CLASS_RT:
			if (!capable(CAP_SYS_ADMIN))
				return -EPERM;
			/* fall through */
			/* rt has prio field too */
		case IOPRIO_CLASS_BE:
			if (data >= IOPRIO_BE_NR || data < 0)
				return -EINVAL;

			break;
		case IOPRIO_CLASS_IDLE:
			break;
		case IOPRIO_CLASS_NONE:
			if (data)
				return -EINVAL;
			break;
		default:
			return -EINVAL;
	}

	return 0;
}