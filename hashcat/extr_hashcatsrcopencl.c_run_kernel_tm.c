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
struct TYPE_3__ {int /*<<< orphan*/  command_queue; int /*<<< orphan*/  kernel_tm; int /*<<< orphan*/  kernel_wgs_tm; } ;
typedef  TYPE_1__ hc_device_param_t ;
typedef  int /*<<< orphan*/  hashcat_ctx_t ;
typedef  int /*<<< orphan*/  cl_kernel ;

/* Variables and functions */
 int MIN (int const,int /*<<< orphan*/ ) ; 
 int hc_clEnqueueNDRangeKernel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,size_t const*,size_t const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hc_clFinish (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hc_clFlush (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int run_kernel_tm (hashcat_ctx_t *hashcat_ctx, hc_device_param_t *device_param)
{
  const u64 num_elements = 1024; // fixed

  const u64 kernel_threads = MIN (num_elements, device_param->kernel_wgs_tm);

  cl_kernel kernel = device_param->kernel_tm;

  const size_t global_work_size[3] = { num_elements,    1, 1 };
  const size_t local_work_size[3]  = { kernel_threads,  1, 1 };

  int CL_rc;

  CL_rc = hc_clEnqueueNDRangeKernel (hashcat_ctx, device_param->command_queue, kernel, 1, NULL, global_work_size, local_work_size, 0, NULL, NULL);

  if (CL_rc == -1) return -1;

  CL_rc = hc_clFlush (hashcat_ctx, device_param->command_queue);

  if (CL_rc == -1) return -1;

  CL_rc = hc_clFinish (hashcat_ctx, device_param->command_queue);

  if (CL_rc == -1) return -1;

  return 0;
}