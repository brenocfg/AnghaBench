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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  preferred_work_group_size_multiple ;
struct TYPE_3__ {int /*<<< orphan*/  opencl_device; } ;
typedef  TYPE_1__ hc_device_param_t ;
typedef  int /*<<< orphan*/  hashcat_ctx_t ;
typedef  int /*<<< orphan*/  cl_kernel ;

/* Variables and functions */
 int /*<<< orphan*/  CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE ; 
 int hc_clGetKernelWorkGroupInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,size_t*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_opencl_kernel_preferred_wgs_multiple (hashcat_ctx_t *hashcat_ctx, hc_device_param_t *device_param, cl_kernel kernel, u32 *result)
{
  size_t preferred_work_group_size_multiple = 0;

  if (hc_clGetKernelWorkGroupInfo (hashcat_ctx, kernel, device_param->opencl_device, CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE, sizeof (preferred_work_group_size_multiple), &preferred_work_group_size_multiple, NULL) == -1) return -1;

  *result = (u32) preferred_work_group_size_multiple;

  return 0;
}