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
typedef  int /*<<< orphan*/  work_group_size ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  opencl_device; } ;
typedef  TYPE_1__ hc_device_param_t ;
typedef  int /*<<< orphan*/  hashcat_ctx_t ;
typedef  int /*<<< orphan*/  compile_work_group_size ;
typedef  int /*<<< orphan*/  cl_kernel ;

/* Variables and functions */
 int /*<<< orphan*/  CL_KERNEL_COMPILE_WORK_GROUP_SIZE ; 
 int /*<<< orphan*/  CL_KERNEL_WORK_GROUP_SIZE ; 
 int /*<<< orphan*/  MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hc_clGetKernelWorkGroupInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,...) ; 

__attribute__((used)) static int get_opencl_kernel_wgs (hashcat_ctx_t *hashcat_ctx, hc_device_param_t *device_param, cl_kernel kernel, u32 *result)
{
  size_t work_group_size = 0;

  if (hc_clGetKernelWorkGroupInfo (hashcat_ctx, kernel, device_param->opencl_device, CL_KERNEL_WORK_GROUP_SIZE, sizeof (work_group_size), &work_group_size, NULL) == -1) return -1;

  u32 kernel_threads = (u32) work_group_size;

  size_t compile_work_group_size[3] = { 0, 0, 0 };

  if (hc_clGetKernelWorkGroupInfo (hashcat_ctx, kernel, device_param->opencl_device, CL_KERNEL_COMPILE_WORK_GROUP_SIZE, sizeof (compile_work_group_size), &compile_work_group_size, NULL) == -1) return -1;

  const size_t cwgs_total = compile_work_group_size[0] * compile_work_group_size[1] * compile_work_group_size[2];

  if (cwgs_total > 0)
  {
    kernel_threads = MIN (kernel_threads, (u32) cwgs_total);
  }

  *result = kernel_threads;

  return 0;
}