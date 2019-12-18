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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int* kernel_params_memset_buf64; int kernel_wgs_memset; int /*<<< orphan*/  cuda_stream; void** kernel_params_memset; int /*<<< orphan*/  cuda_function_memset; int /*<<< orphan*/ * kernel_params_memset_buf32; } ;
typedef  TYPE_1__ hc_device_param_t ;
typedef  int /*<<< orphan*/  hashcat_ctx_t ;
typedef  int /*<<< orphan*/  CUfunction ;
typedef  scalar_t__ CUdeviceptr ;

/* Variables and functions */
 int CEILDIV (int,int const) ; 
 int hc_cuLaunchKernel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int const,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *) ; 
 int hc_cuMemcpyHtoD (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int const) ; 
 int hc_cuStreamSynchronize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int run_cuda_kernel_memset (hashcat_ctx_t *hashcat_ctx, hc_device_param_t *device_param, CUdeviceptr buf, const u32 value, const u64 size)
{
  const u64 num16d = size / 16;
  const u64 num16m = size % 16;

  if (num16d)
  {
    device_param->kernel_params_memset[0]       = (void *) &buf;
    device_param->kernel_params_memset_buf32[1] = value;
    device_param->kernel_params_memset_buf64[2] = num16d;

    const u64 kernel_threads = device_param->kernel_wgs_memset;

    u64 num_elements = num16d;

    num_elements = CEILDIV (num_elements, kernel_threads);

    CUfunction function = device_param->cuda_function_memset;

    //CU_rc = hc_clSetKernelArg (hashcat_ctx, kernel, 0, sizeof (cl_mem),   (void *) &buf);                         if (CU_rc == -1) return -1;
    //CU_rc = hc_clSetKernelArg (hashcat_ctx, kernel, 1, sizeof (cl_uint),  device_param->kernel_params_memset[1]); if (CU_rc == -1) return -1;
    //CU_rc = hc_clSetKernelArg (hashcat_ctx, kernel, 2, sizeof (cl_ulong), device_param->kernel_params_memset[2]); if (CU_rc == -1) return -1;

    //const size_t global_work_size[3] = { num_elements,   1, 1 };
    //const size_t local_work_size[3]  = { kernel_threads, 1, 1 };

    if (hc_cuLaunchKernel (hashcat_ctx, function, num_elements, 1, 1, kernel_threads, 1, 1, 0, device_param->cuda_stream, device_param->kernel_params_memset, NULL) == -1) return -1;

    if (hc_cuStreamSynchronize (hashcat_ctx, device_param->cuda_stream) == -1) return -1;
  }

  if (num16m)
  {
    u32 tmp[4];

    tmp[0] = value;
    tmp[1] = value;
    tmp[2] = value;
    tmp[3] = value;

    // Apparently are allowed to do this: https://devtalk.nvidia.com/default/topic/761515/how-to-copy-to-device-memory-with-offset-/

    if (hc_cuMemcpyHtoD (hashcat_ctx, buf + (num16d * 16), tmp, num16m) == -1) return -1;
  }

  return 0;
}