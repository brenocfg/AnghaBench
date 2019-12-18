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
struct mlxd_foreach_action {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* func ) (int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MLX_NEXT_CHILD ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  ctrlrpath (int) ; 
 int /*<<< orphan*/  drivepath (int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int*) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 

void
mlxd_foreach_ctrlr(int unit, void *arg)
{
    struct mlxd_foreach_action	*ma = (struct mlxd_foreach_action *)arg;
    int				i, fd, ctrlfd;
    
    /* Get the device */
    if ((ctrlfd = open(ctrlrpath(unit), 0)) < 0)
	return;
    
    for (i = -1; ;) {
	/* Get the unit number of the next child device */
	if (ioctl(ctrlfd, MLX_NEXT_CHILD, &i) < 0) {
	    close(ctrlfd);
	    return;
	}
	
	/* check that we can open this unit */
	if ((fd = open(drivepath(i), 0)) >= 0)
	    close(fd);
	/* if we can, do */
	if (fd >= 0) {
	    ma->func(i, ma->arg);
	}
    }
}