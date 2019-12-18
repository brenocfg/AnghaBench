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
struct TYPE_3__ {int /*<<< orphan*/  cuda_stream; void** kernel_params_atinit; int /*<<< orphan*/  cuda_function_atinit; int /*<<< orphan*/  kernel_wgs_atinit; int /*<<< orphan*/ * kernel_params_atinit_buf64; } ;
typedef  TYPE_1__ hc_device_param_t ;
typedef  int /*<<< orphan*/  hashcat_ctx_t ;
typedef  int /*<<< orphan*/  CUfunction ;
typedef  int /*<<< orphan*/  CUdeviceptr ;

/* Variables and functions */
 int /*<<< orphan*/  CEILDIV (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int hc_cuLaunchKernel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/  const,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *) ; 
 int hc_cuStreamSynchronize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int run_cuda_kernel_atinit (hashcat_ctx_t *hashcat_ctx, hc_device_param_t *device_param, CUdeviceptr buf, const u64 num)
{
  u64 num_elements = num;

  device_param->kernel_params_atinit[0]       = (void *) &buf;
  device_param->kernel_params_atinit_buf64[1] = num_elements;

  const u64 kernel_threads = device_param->kernel_wgs_atinit;

  num_elements = CEILDIV (num_elements, kernel_threads);

  CUfunction function = device_param->cuda_function_atinit;

  if (hc_cuLaunchKernel (hashcat_ctx, function, num_elements, 1, 1, kernel_threads, 1, 1, 0, device_param->cuda_stream, device_param->kernel_params_atinit, NULL) == -1) return -1;

  if (hc_cuStreamSynchronize (hashcat_ctx, device_param->cuda_stream) == -1) return -1;

  return 0;
}