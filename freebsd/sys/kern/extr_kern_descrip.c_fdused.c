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
struct filedesc {int fd_lastfile; int fd_freefile; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILEDESC_XLOCK_ASSERT (struct filedesc*) ; 
 int /*<<< orphan*/  fdused_init (struct filedesc*,int) ; 

__attribute__((used)) static void
fdused(struct filedesc *fdp, int fd)
{

	FILEDESC_XLOCK_ASSERT(fdp);

	fdused_init(fdp, fd);
	if (fd > fdp->fd_lastfile)
		fdp->fd_lastfile = fd;
	if (fd == fdp->fd_freefile)
		fdp->fd_freefile++;
}