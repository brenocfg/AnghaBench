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
typedef  int u_long ;
struct thread {int dummy; } ;
struct pfilioc_list {int dummy; } ;
struct pfilioc_link {int dummy; } ;
struct cdev {int dummy; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  PFILIOC_LINK 130 
#define  PFILIOC_LISTHEADS 129 
#define  PFILIOC_LISTHOOKS 128 
 int /*<<< orphan*/  TD_TO_VNET (struct thread*) ; 
 int pfilioc_link (struct pfilioc_link*) ; 
 int pfilioc_listheads (struct pfilioc_list*) ; 
 int pfilioc_listhooks (struct pfilioc_list*) ; 

__attribute__((used)) static int
pfil_ioctl(struct cdev *dev, u_long cmd, caddr_t addr, int flags,
    struct thread *td)
{
	int error;

	CURVNET_SET(TD_TO_VNET(td));
	error = 0;
	switch (cmd) {
	case PFILIOC_LISTHEADS:
		error = pfilioc_listheads((struct pfilioc_list *)addr);
		break;
	case PFILIOC_LISTHOOKS:
		error = pfilioc_listhooks((struct pfilioc_list *)addr);
		break;
	case PFILIOC_LINK:
		error = pfilioc_link((struct pfilioc_link *)addr);
		break;
	default:
		error = EINVAL;
		break;
	}
	CURVNET_RESTORE();
	return (error);
}