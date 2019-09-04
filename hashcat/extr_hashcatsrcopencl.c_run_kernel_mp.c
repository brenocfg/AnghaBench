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
typedef  int u32 ;
struct TYPE_3__ {int* kernel_params_mp_buf64; int* kernel_params_mp_r_buf64; int* kernel_params_mp_l_buf64; int kernel_wgs_mp; int kernel_wgs_mp_r; int kernel_wgs_mp_l; int /*<<< orphan*/  command_queue; int /*<<< orphan*/ * kernel_params_mp_l; int /*<<< orphan*/ * kernel_params_mp_r; int /*<<< orphan*/ * kernel_params_mp; int /*<<< orphan*/ * kernel_mp_l; int /*<<< orphan*/ * kernel_mp_r; int /*<<< orphan*/ * kernel_mp; } ;
typedef  TYPE_1__ hc_device_param_t ;
typedef  int /*<<< orphan*/  hashcat_ctx_t ;
typedef  int /*<<< orphan*/  cl_ulong ;
typedef  int /*<<< orphan*/  cl_uint ;
typedef  int /*<<< orphan*/ * cl_kernel ;

/* Variables and functions */
#define  KERN_RUN_MP 130 
#define  KERN_RUN_MP_L 129 
#define  KERN_RUN_MP_R 128 
 int /*<<< orphan*/  event_log_error (int /*<<< orphan*/ *,char*) ; 
 int hc_clEnqueueNDRangeKernel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,size_t const*,size_t const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hc_clFinish (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hc_clFlush (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hc_clSetKernelArg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int round_up_multiple_64 (int,int) ; 

int run_kernel_mp (hashcat_ctx_t *hashcat_ctx, hc_device_param_t *device_param, const u32 kern_run, const u64 num)
{
  u64 num_elements = num;

  switch (kern_run)
  {
    case KERN_RUN_MP:   device_param->kernel_params_mp_buf64[8]   = num; break;
    case KERN_RUN_MP_R: device_param->kernel_params_mp_r_buf64[8] = num; break;
    case KERN_RUN_MP_L: device_param->kernel_params_mp_l_buf64[9] = num; break;
  }

  u64       kernel_threads = 0;
  cl_kernel kernel = NULL;

  switch (kern_run)
  {
    case KERN_RUN_MP:
      kernel          = device_param->kernel_mp;
      kernel_threads  = device_param->kernel_wgs_mp;
      break;
    case KERN_RUN_MP_R:
      kernel          = device_param->kernel_mp_r;
      kernel_threads  = device_param->kernel_wgs_mp_r;
      break;
    case KERN_RUN_MP_L:
      kernel          = device_param->kernel_mp_l;
      kernel_threads  = device_param->kernel_wgs_mp_l;
      break;
    default:
      event_log_error (hashcat_ctx, "Invalid kernel specified.");
      return -1;
  }

  num_elements = round_up_multiple_64 (num_elements, kernel_threads);

  int CL_rc;

  switch (kern_run)
  {
    case KERN_RUN_MP:   CL_rc = hc_clSetKernelArg (hashcat_ctx, kernel, 3, sizeof (cl_ulong), device_param->kernel_params_mp[3]);   if (CL_rc == -1) return -1;
                        CL_rc = hc_clSetKernelArg (hashcat_ctx, kernel, 4, sizeof (cl_uint),  device_param->kernel_params_mp[4]);   if (CL_rc == -1) return -1;
                        CL_rc = hc_clSetKernelArg (hashcat_ctx, kernel, 5, sizeof (cl_uint),  device_param->kernel_params_mp[5]);   if (CL_rc == -1) return -1;
                        CL_rc = hc_clSetKernelArg (hashcat_ctx, kernel, 6, sizeof (cl_uint),  device_param->kernel_params_mp[6]);   if (CL_rc == -1) return -1;
                        CL_rc = hc_clSetKernelArg (hashcat_ctx, kernel, 7, sizeof (cl_uint),  device_param->kernel_params_mp[7]);   if (CL_rc == -1) return -1;
                        CL_rc = hc_clSetKernelArg (hashcat_ctx, kernel, 8, sizeof (cl_ulong), device_param->kernel_params_mp[8]);   if (CL_rc == -1) return -1;
                        break;
    case KERN_RUN_MP_R: CL_rc = hc_clSetKernelArg (hashcat_ctx, kernel, 3, sizeof (cl_ulong), device_param->kernel_params_mp_r[3]); if (CL_rc == -1) return -1;
                        CL_rc = hc_clSetKernelArg (hashcat_ctx, kernel, 4, sizeof (cl_uint),  device_param->kernel_params_mp_r[4]); if (CL_rc == -1) return -1;
                        CL_rc = hc_clSetKernelArg (hashcat_ctx, kernel, 5, sizeof (cl_uint),  device_param->kernel_params_mp_r[5]); if (CL_rc == -1) return -1;
                        CL_rc = hc_clSetKernelArg (hashcat_ctx, kernel, 6, sizeof (cl_uint),  device_param->kernel_params_mp_r[6]); if (CL_rc == -1) return -1;
                        CL_rc = hc_clSetKernelArg (hashcat_ctx, kernel, 7, sizeof (cl_uint),  device_param->kernel_params_mp_r[7]); if (CL_rc == -1) return -1;
                        CL_rc = hc_clSetKernelArg (hashcat_ctx, kernel, 8, sizeof (cl_ulong), device_param->kernel_params_mp_r[8]); if (CL_rc == -1) return -1;
                        break;
    case KERN_RUN_MP_L: CL_rc = hc_clSetKernelArg (hashcat_ctx, kernel, 3, sizeof (cl_ulong), device_param->kernel_params_mp_l[3]); if (CL_rc == -1) return -1;
                        CL_rc = hc_clSetKernelArg (hashcat_ctx, kernel, 4, sizeof (cl_uint),  device_param->kernel_params_mp_l[4]); if (CL_rc == -1) return -1;
                        CL_rc = hc_clSetKernelArg (hashcat_ctx, kernel, 5, sizeof (cl_uint),  device_param->kernel_params_mp_l[5]); if (CL_rc == -1) return -1;
                        CL_rc = hc_clSetKernelArg (hashcat_ctx, kernel, 6, sizeof (cl_uint),  device_param->kernel_params_mp_l[6]); if (CL_rc == -1) return -1;
                        CL_rc = hc_clSetKernelArg (hashcat_ctx, kernel, 7, sizeof (cl_uint),  device_param->kernel_params_mp_l[7]); if (CL_rc == -1) return -1;
                        CL_rc = hc_clSetKernelArg (hashcat_ctx, kernel, 8, sizeof (cl_uint),  device_param->kernel_params_mp_l[8]); if (CL_rc == -1) return -1;
                        CL_rc = hc_clSetKernelArg (hashcat_ctx, kernel, 9, sizeof (cl_ulong), device_param->kernel_params_mp_l[9]); if (CL_rc == -1) return -1;
                        break;
  }

  const size_t global_work_size[3] = { num_elements,   1, 1 };
  const size_t local_work_size[3]  = { kernel_threads, 1, 1 };

  CL_rc = hc_clEnqueueNDRangeKernel (hashcat_ctx, device_param->command_queue, kernel, 1, NULL, global_work_size, local_work_size, 0, NULL, NULL);

  if (CL_rc == -1) return -1;

  CL_rc = hc_clFlush (hashcat_ctx, device_param->command_queue);

  if (CL_rc == -1) return -1;

  CL_rc = hc_clFinish (hashcat_ctx, device_param->command_queue);

  if (CL_rc == -1) return -1;

  return 0;
}