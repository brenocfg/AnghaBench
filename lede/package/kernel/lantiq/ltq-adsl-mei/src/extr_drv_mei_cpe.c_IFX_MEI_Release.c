#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  i_rdev; } ;
typedef  TYPE_1__ DSL_DRV_inode_t ;
typedef  int /*<<< orphan*/  DSL_DRV_file_t ;
typedef  int /*<<< orphan*/  DSL_DEV_Device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DSL_BSP_DriverHandleDelete (int /*<<< orphan*/ *) ; 
 int EIO ; 
 int MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dsl_devices ; 

__attribute__((used)) static int
IFX_MEI_Release (DSL_DRV_inode_t * ino, DSL_DRV_file_t * fil)
{
	//int maj = MAJOR(ino->i_rdev);
	int num = MINOR (ino->i_rdev);
	DSL_DEV_Device_t *pDev;

	pDev = &dsl_devices[num];
	if (pDev == NULL)
		return -EIO;
	DSL_BSP_DriverHandleDelete (pDev);
	return 0;
}