#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct wtap_hal {int /*<<< orphan*/  hal_md; } ;
struct TYPE_3__ {struct wtap_hal* wp_hal; } ;
struct visibility_plugin {TYPE_1__ base; } ;
struct thread {int dummy; } ;
struct link {int op; int id1; int id2; } ;
struct cdev {scalar_t__ si_drv1; } ;
typedef  scalar_t__ caddr_t ;
struct TYPE_4__ {int /*<<< orphan*/  td_ucred; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRED_TO_VNET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWTAP_PRINTF (char*) ; 
 int EINVAL ; 
#define  VISIOCTLLINK 129 
#define  VISIOCTLOPEN 128 
 int /*<<< orphan*/  add_link (struct visibility_plugin*,struct link*) ; 
 TYPE_2__* curthread ; 
 int /*<<< orphan*/  del_link (struct visibility_plugin*,struct link*) ; 
 int /*<<< orphan*/  medium_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  medium_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 

int
vis_ioctl(struct cdev *sdev, u_long cmd, caddr_t data,
    int fflag, struct thread *td)
{
	struct visibility_plugin *vis_plugin =
	    (struct visibility_plugin *) sdev->si_drv1;
	struct wtap_hal *hal = vis_plugin->base.wp_hal;
	struct link l;
	int op;
	int error = 0;

	CURVNET_SET(CRED_TO_VNET(curthread->td_ucred));
	switch(cmd) {
	case VISIOCTLOPEN:
		op =  *(int *)data; 
		if(op == 0)
			medium_close(hal->hal_md);
		else
			medium_open(hal->hal_md);
		break;
	case VISIOCTLLINK:
		l = *(struct link *)data;
		if(l.op == 0)
			del_link(vis_plugin, &l);
		else
			add_link(vis_plugin, &l);
#if 0
		printf("op=%d, id1=%d, id2=%d\n", l.op, l.id1, l.id2);
#endif
		break;
	default:
		DWTAP_PRINTF("Unknown WTAP IOCTL\n");
		error = EINVAL;
	}

	CURVNET_RESTORE();
	return error;
}