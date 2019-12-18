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
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_3__ {scalar_t__ private_data; } ;
typedef  TYPE_1__ DSL_DRV_file_t ;
typedef  scalar_t__ DSL_DEV_MeiError_t ;
typedef  int /*<<< orphan*/  DSL_DEV_Device_t ;

/* Variables and functions */
 scalar_t__ DSL_BSP_FWDownload (int /*<<< orphan*/ *,char const*,size_t,long*,long*) ; 
 scalar_t__ DSL_DEV_MEI_ERR_FAILURE ; 
 int /*<<< orphan*/  EIO ; 

__attribute__((used)) static ssize_t
IFX_MEI_Write (DSL_DRV_file_t * filp, const char *buf, size_t size, loff_t * loff)
{
	DSL_DEV_MeiError_t mei_error = DSL_DEV_MEI_ERR_FAILURE;
	long offset = 0;
	DSL_DEV_Device_t *pDev = (DSL_DEV_Device_t *) filp->private_data;

	if (pDev == NULL)
		return -EIO;

	mei_error =
		DSL_BSP_FWDownload (pDev, buf, size, (long *) loff,  &offset);

	if (mei_error == DSL_DEV_MEI_ERR_FAILURE)
		return -EIO;
	return (ssize_t) offset;
}