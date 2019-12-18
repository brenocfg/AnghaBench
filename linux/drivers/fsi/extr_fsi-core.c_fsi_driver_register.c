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
struct fsi_driver {int /*<<< orphan*/  drv; int /*<<< orphan*/  id_table; } ;

/* Variables and functions */
 int EINVAL ; 
 int driver_register (int /*<<< orphan*/ *) ; 

int fsi_driver_register(struct fsi_driver *fsi_drv)
{
	if (!fsi_drv)
		return -EINVAL;
	if (!fsi_drv->id_table)
		return -EINVAL;

	return driver_register(&fsi_drv->drv);
}