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
struct filedesc {int /*<<< orphan*/ * fd_jdir; int /*<<< orphan*/ * fd_rdir; int /*<<< orphan*/ * fd_cdir; } ;

/* Variables and functions */
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  fdescfree_fds (int /*<<< orphan*/ ,struct filedesc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vrele (int /*<<< orphan*/ *) ; 

void
fdescfree_remapped(struct filedesc *fdp)
{

	if (fdp->fd_cdir != NULL)
		vrele(fdp->fd_cdir);
	if (fdp->fd_rdir != NULL)
		vrele(fdp->fd_rdir);
	if (fdp->fd_jdir != NULL)
		vrele(fdp->fd_jdir);

	fdescfree_fds(curthread, fdp, 0);
}