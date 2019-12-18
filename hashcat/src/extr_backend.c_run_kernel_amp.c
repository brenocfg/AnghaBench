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
struct TYPE_3__ {int* kernel_params_amp_buf64; int kernel_wgs_amp; int is_cuda; int is_opencl; int /*<<< orphan*/  opencl_command_queue; int /*<<< orphan*/ * kernel_params_amp; int /*<<< orphan*/  opencl_kernel_amp; int /*<<< orphan*/  cuda_stream; int /*<<< orphan*/  cuda_function_amp; } ;
typedef  TYPE_1__ hc_device_param_t ;
typedef  int /*<<< orphan*/  hashcat_ctx_t ;
typedef  int /*<<< orphan*/  cl_ulong ;
typedef  int /*<<< orphan*/  cl_kernel ;
typedef  int /*<<< orphan*/  CUfunction ;

/* Variables and functions */
 int CEILDIV (int,int const) ; 
 int hc_clEnqueueNDRangeKernel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,size_t const*,size_t const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hc_clFinish (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hc_clFlush (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hc_clSetKernelArg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int hc_cuLaunchKernel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int const,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hc_cuStreamSynchronize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int round_up_multiple_64 (int,int const) ; 

int run_kernel_amp (hashcat_ctx_t *hashcat_ctx, hc_device_param_t *device_param, const u64 num)
{
  device_param->kernel_params_amp_buf64[6] = num;

  u64 num_elements = num;

  const u64 kernel_threads = device_param->kernel_wgs_amp;

  if (device_param->is_cuda == true)
  {
    num_elements = CEILDIV (num_elements, kernel_threads);

    CUfunction cuda_function = device_param->cuda_function_amp;

    if (hc_cuLaunchKernel (hashcat_ctx, cuda_function, num_elements, 1, 1, kernel_threads, 1, 1, 0, device_param->cuda_stream, device_param->kernel_params_amp, NULL) == -1) return -1;

    if (hc_cuStreamSynchronize (hashcat_ctx, device_param->cuda_stream) == -1) return -1;
  }

  if (device_param->is_opencl == true)
  {
    num_elements = round_up_multiple_64 (num_elements, kernel_threads);

    cl_kernel opencl_kernel = device_param->opencl_kernel_amp;

    if (hc_clSetKernelArg (hashcat_ctx, opencl_kernel, 6, sizeof (cl_ulong), device_param->kernel_params_amp[6]) == -1) return -1;

    const size_t global_work_size[3] = { num_elements,    1, 1 };
    const size_t local_work_size[3]  = { kernel_threads,  1, 1 };

    if (hc_clEnqueueNDRangeKernel (hashcat_ctx, device_param->opencl_command_queue, opencl_kernel, 1, NULL, global_work_size, local_work_size, 0, NULL, NULL) == -1) return -1;

    if (hc_clFlush (hashcat_ctx, device_param->opencl_command_queue)  == -1) return -1;

    if (hc_clFinish (hashcat_ctx, device_param->opencl_command_queue) == -1) return -1;
  }

  return 0;
}