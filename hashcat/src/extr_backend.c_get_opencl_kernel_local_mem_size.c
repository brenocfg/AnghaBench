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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  local_mem_size ;
struct TYPE_3__ {int /*<<< orphan*/  opencl_device; } ;
typedef  TYPE_1__ hc_device_param_t ;
typedef  int /*<<< orphan*/  hashcat_ctx_t ;
typedef  int /*<<< orphan*/  cl_ulong ;
typedef  int /*<<< orphan*/  cl_kernel ;

/* Variables and functions */
 int /*<<< orphan*/  CL_KERNEL_LOCAL_MEM_SIZE ; 
 int hc_clGetKernelWorkGroupInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_opencl_kernel_local_mem_size (hashcat_ctx_t *hashcat_ctx, hc_device_param_t *device_param, cl_kernel kernel, u64 *result)
{
  cl_ulong local_mem_size = 0;

  if (hc_clGetKernelWorkGroupInfo (hashcat_ctx, kernel, device_param->opencl_device, CL_KERNEL_LOCAL_MEM_SIZE, sizeof (local_mem_size), &local_mem_size, NULL) == -1) return -1;

  *result = local_mem_size;

  return 0;
}