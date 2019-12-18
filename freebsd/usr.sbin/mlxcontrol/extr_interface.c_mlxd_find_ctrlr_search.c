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
struct TYPE_2__ {int unit; int ctrlr; int sysdrive; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX_GET_SYSDRIVE ; 
 int /*<<< orphan*/  MLX_NEXT_CHILD ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  ctrlrpath (int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int*) ; 
 TYPE_1__ mlxd_find_ctrlr_param ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mlxd_find_ctrlr_search(int unit, void *arg)
{
    int				i, fd;
    
    /* Get the device */
    if ((fd = open(ctrlrpath(unit), 0)) >= 0) {
	for (i = -1; ;) {
	    /* Get the unit number of the next child device */
	    if (ioctl(fd, MLX_NEXT_CHILD, &i) < 0)
		break;

	    /* is this child the unit we want? */
	    if (i == mlxd_find_ctrlr_param.unit) {
		mlxd_find_ctrlr_param.ctrlr = unit;
		if (ioctl(fd, MLX_GET_SYSDRIVE, &i) == 0)
		    mlxd_find_ctrlr_param.sysdrive = i;
	    }
	}
	close(fd);
    }
}