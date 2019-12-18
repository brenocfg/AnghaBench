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
struct TYPE_2__ {int nonblock; int async; int /*<<< orphan*/  sigio; } ;

/* Variables and functions */
 int ENOTTY ; 
#define  FIOASYNC 134 
#define  FIOCLEX 133 
#define  FIOGETOWN 132 
#define  FIONBIO 131 
#define  FIONCLEX 130 
#define  FIONREAD 129 
#define  FIOSETOWN 128 
 TYPE_1__ devsoftc ; 
 int fgetown (int /*<<< orphan*/ *) ; 
 int fsetown (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static	int
devioctl(struct cdev *dev, u_long cmd, caddr_t data, int fflag, struct thread *td)
{
	switch (cmd) {

	case FIONBIO:
		if (*(int*)data)
			devsoftc.nonblock = 1;
		else
			devsoftc.nonblock = 0;
		return (0);
	case FIOASYNC:
		if (*(int*)data)
			devsoftc.async = 1;
		else
			devsoftc.async = 0;
		return (0);
	case FIOSETOWN:
		return fsetown(*(int *)data, &devsoftc.sigio);
	case FIOGETOWN:
		*(int *)data = fgetown(&devsoftc.sigio);
		return (0);

		/* (un)Support for other fcntl() calls. */
	case FIOCLEX:
	case FIONCLEX:
	case FIONREAD:
	default:
		break;
	}
	return (ENOTTY);
}