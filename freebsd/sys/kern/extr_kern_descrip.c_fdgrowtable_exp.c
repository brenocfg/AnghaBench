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
struct filedesc {int fd_nfiles; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILEDESC_XLOCK_ASSERT (struct filedesc*) ; 
 int /*<<< orphan*/  fdgrowtable (struct filedesc*,int) ; 

__attribute__((used)) static void
fdgrowtable_exp(struct filedesc *fdp, int nfd)
{
	int nfd1;

	FILEDESC_XLOCK_ASSERT(fdp);

	nfd1 = fdp->fd_nfiles * 2;
	if (nfd1 < nfd)
		nfd1 = nfd;
	fdgrowtable(fdp, nfd1);
}