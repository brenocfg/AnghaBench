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
typedef  int u_long ;
struct thread {int dummy; } ;
struct cdev {int dummy; } ;
typedef  scalar_t__ caddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  td_ucred; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRED_TO_VNET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWTAP_PRINTF (char*) ; 
 int EINVAL ; 
#define  WTAPIOCTLCRT 129 
#define  WTAPIOCTLDEL 128 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/  free_wtap (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hal ; 
 int /*<<< orphan*/  new_wtap (int /*<<< orphan*/ ,int) ; 

int
wtap_ioctl(struct cdev *dev, u_long cmd, caddr_t data,
    int fflag, struct thread *td)
{
	int error = 0;

	CURVNET_SET(CRED_TO_VNET(curthread->td_ucred));

	switch(cmd) {
	case WTAPIOCTLCRT:
		if(new_wtap(hal, *(int *)data))
			error = EINVAL;
		break;
	case WTAPIOCTLDEL:
		if(free_wtap(hal, *(int *)data))
			error = EINVAL;
		break;
	default:
		DWTAP_PRINTF("Unknown WTAP IOCTL\n");
		error = EINVAL;
	}

	CURVNET_RESTORE();
	return error;
}