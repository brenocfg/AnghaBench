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
struct filedesc {int /*<<< orphan*/ * fd_rdir; int /*<<< orphan*/ * fd_cdir; } ;
struct TYPE_2__ {struct filedesc* p_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILEDESC_XLOCK (struct filedesc*) ; 
 int /*<<< orphan*/  FILEDESC_XUNLOCK (struct filedesc*) ; 
 TYPE_1__* curproc ; 
 void* rootvnode ; 
 int /*<<< orphan*/  vrefact (void*) ; 

void
pwd_ensure_dirs(void)
{
	struct filedesc *fdp;

	fdp = curproc->p_fd;
	FILEDESC_XLOCK(fdp);
	if (fdp->fd_cdir == NULL) {
		fdp->fd_cdir = rootvnode;
		vrefact(rootvnode);
	}
	if (fdp->fd_rdir == NULL) {
		fdp->fd_rdir = rootvnode;
		vrefact(rootvnode);
	}
	FILEDESC_XUNLOCK(fdp);
}