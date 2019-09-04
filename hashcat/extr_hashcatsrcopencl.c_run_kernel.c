#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ attack_mode; } ;
typedef  TYPE_1__ user_options_t ;
typedef  int /*<<< orphan*/  useconds_t ;
typedef  int u64 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  time_start ;
typedef  int /*<<< orphan*/  time_end ;
struct TYPE_18__ {scalar_t__ devices_status; } ;
typedef  TYPE_2__ status_ctx_t ;
struct TYPE_19__ {int* kernel_params_buf64; int kernel_wgs1; int kernel_wgs12; int kernel_wgs2; int kernel_wgs23; int kernel_wgs3; int kernel_wgs4; int kernel_wgs_init2; int kernel_wgs_loop2; int kernel_wgs_aux1; int kernel_wgs_aux2; int kernel_wgs_aux3; int kernel_wgs_aux4; double spin_damp; int* exec_us_prev1; int* exec_us_prev2; int* exec_us_prev3; int* exec_us_prev4; int* exec_us_prev_init2; int* exec_us_prev_loop2; int* exec_us_prev_aux1; int* exec_us_prev_aux2; int* exec_us_prev_aux3; int* exec_us_prev_aux4; int exec_pos; double* exec_msec; int /*<<< orphan*/  command_queue; int /*<<< orphan*/  vector_width; int /*<<< orphan*/ * kernel_params; int /*<<< orphan*/  kernel_threads; int /*<<< orphan*/ * kernel_aux4; int /*<<< orphan*/ * kernel_aux3; int /*<<< orphan*/ * kernel_aux2; int /*<<< orphan*/ * kernel_aux1; int /*<<< orphan*/ * kernel_loop2; int /*<<< orphan*/ * kernel_init2; int /*<<< orphan*/ * kernel4; int /*<<< orphan*/ * kernel3; int /*<<< orphan*/ * kernel23; int /*<<< orphan*/ * kernel2; int /*<<< orphan*/ * kernel12; int /*<<< orphan*/ * kernel1; } ;
typedef  TYPE_3__ hc_device_param_t ;
struct TYPE_20__ {int opts_type; int opti_type; } ;
typedef  TYPE_4__ hashconfig_t ;
struct TYPE_21__ {TYPE_1__* user_options; TYPE_2__* status_ctx; TYPE_4__* hashconfig; } ;
typedef  TYPE_5__ hashcat_ctx_t ;
typedef  int /*<<< orphan*/  event_status ;
typedef  scalar_t__ cl_ulong ;
typedef  int /*<<< orphan*/  cl_uint ;
typedef  int /*<<< orphan*/  cl_mem ;
typedef  int /*<<< orphan*/ * cl_kernel ;
typedef  scalar_t__ cl_int ;
typedef  int /*<<< orphan*/  cl_event ;

/* Variables and functions */
 scalar_t__ ATTACK_MODE_BF ; 
 int CEILDIV (int,int /*<<< orphan*/ ) ; 
 scalar_t__ CL_COMPLETE ; 
 int /*<<< orphan*/  CL_EVENT_COMMAND_EXECUTION_STATUS ; 
 int /*<<< orphan*/  CL_PROFILING_COMMAND_END ; 
 int /*<<< orphan*/  CL_PROFILING_COMMAND_START ; 
 int EXEC_CACHE ; 
 int const EXPECTED_ITERATIONS ; 
#define  KERN_RUN_1 139 
#define  KERN_RUN_12 138 
#define  KERN_RUN_2 137 
#define  KERN_RUN_23 136 
#define  KERN_RUN_3 135 
#define  KERN_RUN_4 134 
#define  KERN_RUN_AUX1 133 
#define  KERN_RUN_AUX2 132 
#define  KERN_RUN_AUX3 131 
#define  KERN_RUN_AUX4 130 
#define  KERN_RUN_INIT2 129 
#define  KERN_RUN_LOOP2 128 
 int MIN (int,int /*<<< orphan*/ ) ; 
 int OPTI_TYPE_SLOW_HASH_SIMD_COMP ; 
 int OPTI_TYPE_SLOW_HASH_SIMD_INIT ; 
 int OPTI_TYPE_SLOW_HASH_SIMD_LOOP ; 
 int OPTS_TYPE_PT_BITSLICE ; 
 scalar_t__ STATUS_RUNNING ; 
 int /*<<< orphan*/  event_log_error (TYPE_5__*,char*) ; 
 int hc_clEnqueueNDRangeKernel (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,size_t const*,size_t const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hc_clFinish (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int hc_clFlush (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int hc_clGetEventInfo (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*,size_t*) ; 
 int hc_clGetEventProfilingInfo (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 int hc_clReleaseEvent (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int hc_clSetKernelArg (TYPE_5__*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int hc_clWaitForEvents (TYPE_5__*,int,int /*<<< orphan*/ *) ; 
 int round_up_multiple_64 (int,int) ; 
 int /*<<< orphan*/  sleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep (int /*<<< orphan*/ ) ; 

int run_kernel (hashcat_ctx_t *hashcat_ctx, hc_device_param_t *device_param, const u32 kern_run, const u64 num, const u32 event_update, const u32 iteration)
{
  const hashconfig_t   *hashconfig   = hashcat_ctx->hashconfig;
  const status_ctx_t   *status_ctx   = hashcat_ctx->status_ctx;
  const user_options_t *user_options = hashcat_ctx->user_options;

  u64 num_elements = num;

  device_param->kernel_params_buf64[34] = num;

  u64       kernel_threads = 0;
  cl_kernel kernel = NULL;

  switch (kern_run)
  {
    case KERN_RUN_1:
      kernel          = device_param->kernel1;
      kernel_threads  = device_param->kernel_wgs1;
      break;
    case KERN_RUN_12:
      kernel          = device_param->kernel12;
      kernel_threads  = device_param->kernel_wgs12;
      break;
    case KERN_RUN_2:
      kernel          = device_param->kernel2;
      kernel_threads  = device_param->kernel_wgs2;
      break;
    case KERN_RUN_23:
      kernel          = device_param->kernel23;
      kernel_threads  = device_param->kernel_wgs23;
      break;
    case KERN_RUN_3:
      kernel          = device_param->kernel3;
      kernel_threads  = device_param->kernel_wgs3;
      break;
    case KERN_RUN_4:
      kernel          = device_param->kernel4;
      kernel_threads  = device_param->kernel_wgs4;
      break;
    case KERN_RUN_INIT2:
      kernel          = device_param->kernel_init2;
      kernel_threads  = device_param->kernel_wgs_init2;
      break;
    case KERN_RUN_LOOP2:
      kernel          = device_param->kernel_loop2;
      kernel_threads  = device_param->kernel_wgs_loop2;
      break;
    case KERN_RUN_AUX1:
      kernel          = device_param->kernel_aux1;
      kernel_threads  = device_param->kernel_wgs_aux1;
      break;
    case KERN_RUN_AUX2:
      kernel          = device_param->kernel_aux2;
      kernel_threads  = device_param->kernel_wgs_aux2;
      break;
    case KERN_RUN_AUX3:
      kernel          = device_param->kernel_aux3;
      kernel_threads  = device_param->kernel_wgs_aux3;
      break;
    case KERN_RUN_AUX4:
      kernel          = device_param->kernel_aux4;
      kernel_threads  = device_param->kernel_wgs_aux4;
      break;
    default:
      event_log_error (hashcat_ctx, "Invalid kernel specified.");
      return -1;
  }

  kernel_threads = MIN (kernel_threads, device_param->kernel_threads);

  // kernel_threads = power_of_two_floor_32 (kernel_threads);

  num_elements = round_up_multiple_64 (num_elements, kernel_threads);

  int CL_rc;

  for (u32 i = 0; i <= 23; i++)
  {
    CL_rc = hc_clSetKernelArg (hashcat_ctx, kernel, i, sizeof (cl_mem), device_param->kernel_params[i]);

    if (CL_rc == -1) return -1;
  }

  for (u32 i = 24; i <= 33; i++)
  {
    CL_rc = hc_clSetKernelArg (hashcat_ctx, kernel, i, sizeof (cl_uint), device_param->kernel_params[i]);

    if (CL_rc == -1) return -1;
  }

  for (u32 i = 34; i <= 34; i++)
  {
    CL_rc = hc_clSetKernelArg (hashcat_ctx, kernel, i, sizeof (cl_ulong), device_param->kernel_params[i]);

    if (CL_rc == -1) return -1;
  }

  cl_event event;

  if ((hashconfig->opts_type & OPTS_TYPE_PT_BITSLICE) && (user_options->attack_mode == ATTACK_MODE_BF))
  {
    const size_t global_work_size[3] = { num_elements,  32, 1 };
    const size_t local_work_size[3]  = { kernel_threads, 1, 1 };

    CL_rc = hc_clEnqueueNDRangeKernel (hashcat_ctx, device_param->command_queue, kernel, 2, NULL, global_work_size, local_work_size, 0, NULL, &event);

    if (CL_rc == -1) return -1;
  }
  else
  {
    if (kern_run == KERN_RUN_1)
    {
      if (hashconfig->opti_type & OPTI_TYPE_SLOW_HASH_SIMD_INIT)
      {
        num_elements = CEILDIV (num_elements, device_param->vector_width);
      }
    }
    else if (kern_run == KERN_RUN_2)
    {
      if (hashconfig->opti_type & OPTI_TYPE_SLOW_HASH_SIMD_LOOP)
      {
        num_elements = CEILDIV (num_elements, device_param->vector_width);
      }
    }
    else if (kern_run == KERN_RUN_3)
    {
      if (hashconfig->opti_type & OPTI_TYPE_SLOW_HASH_SIMD_COMP)
      {
        num_elements = CEILDIV (num_elements, device_param->vector_width);
      }
    }

    num_elements = round_up_multiple_64 (num_elements, kernel_threads);

    const size_t global_work_size[3] = { num_elements,   1, 1 };
    const size_t local_work_size[3]  = { kernel_threads, 1, 1 };

    CL_rc = hc_clEnqueueNDRangeKernel (hashcat_ctx, device_param->command_queue, kernel, 1, NULL, global_work_size, local_work_size, 0, NULL, &event);

    if (CL_rc == -1) return -1;
  }

  CL_rc = hc_clFlush (hashcat_ctx, device_param->command_queue);

  if (CL_rc == -1) return -1;

  // spin damper section

  const u32 iterationm = iteration % EXPECTED_ITERATIONS;

  cl_int event_status;

  size_t param_value_size_ret;

  CL_rc = hc_clGetEventInfo (hashcat_ctx, event, CL_EVENT_COMMAND_EXECUTION_STATUS, sizeof (event_status), &event_status, &param_value_size_ret);

  if (CL_rc == -1) return -1;

  if (device_param->spin_damp > 0)
  {
    double spin_total = device_param->spin_damp;

    while (event_status != CL_COMPLETE)
    {
      if (status_ctx->devices_status == STATUS_RUNNING)
      {
        switch (kern_run)
        {
          case KERN_RUN_1:      if (device_param->exec_us_prev1[iterationm]      > 0) usleep ((useconds_t) (device_param->exec_us_prev1[iterationm]      * device_param->spin_damp)); break;
          case KERN_RUN_2:      if (device_param->exec_us_prev2[iterationm]      > 0) usleep ((useconds_t) (device_param->exec_us_prev2[iterationm]      * device_param->spin_damp)); break;
          case KERN_RUN_3:      if (device_param->exec_us_prev3[iterationm]      > 0) usleep ((useconds_t) (device_param->exec_us_prev3[iterationm]      * device_param->spin_damp)); break;
          case KERN_RUN_4:      if (device_param->exec_us_prev4[iterationm]      > 0) usleep ((useconds_t) (device_param->exec_us_prev4[iterationm]      * device_param->spin_damp)); break;
          case KERN_RUN_INIT2:  if (device_param->exec_us_prev_init2[iterationm] > 0) usleep ((useconds_t) (device_param->exec_us_prev_init2[iterationm] * device_param->spin_damp)); break;
          case KERN_RUN_LOOP2:  if (device_param->exec_us_prev_loop2[iterationm] > 0) usleep ((useconds_t) (device_param->exec_us_prev_loop2[iterationm] * device_param->spin_damp)); break;
          case KERN_RUN_AUX1:   if (device_param->exec_us_prev_aux1[iterationm]  > 0) usleep ((useconds_t) (device_param->exec_us_prev_aux1[iterationm]  * device_param->spin_damp)); break;
          case KERN_RUN_AUX2:   if (device_param->exec_us_prev_aux2[iterationm]  > 0) usleep ((useconds_t) (device_param->exec_us_prev_aux2[iterationm]  * device_param->spin_damp)); break;
          case KERN_RUN_AUX3:   if (device_param->exec_us_prev_aux3[iterationm]  > 0) usleep ((useconds_t) (device_param->exec_us_prev_aux3[iterationm]  * device_param->spin_damp)); break;
          case KERN_RUN_AUX4:   if (device_param->exec_us_prev_aux4[iterationm]  > 0) usleep ((useconds_t) (device_param->exec_us_prev_aux4[iterationm]  * device_param->spin_damp)); break;
        }
      }
      else
      {
        // we were told to be nice

        sleep (0);
      }

      CL_rc = hc_clGetEventInfo (hashcat_ctx, event, CL_EVENT_COMMAND_EXECUTION_STATUS, sizeof (event_status), &event_status, &param_value_size_ret);

      if (CL_rc == -1) return -1;

      spin_total += device_param->spin_damp;

      if (spin_total > 1) break;
    }
  }

  CL_rc = hc_clWaitForEvents (hashcat_ctx, 1, &event);

  if (CL_rc == -1) return -1;

  cl_ulong time_start;
  cl_ulong time_end;

  CL_rc = hc_clGetEventProfilingInfo (hashcat_ctx, event, CL_PROFILING_COMMAND_START, sizeof (time_start), &time_start, NULL); if (CL_rc == -1) return -1;
  CL_rc = hc_clGetEventProfilingInfo (hashcat_ctx, event, CL_PROFILING_COMMAND_END,   sizeof (time_end),   &time_end,   NULL); if (CL_rc == -1) return -1;

  const double exec_us = (double) (time_end - time_start) / 1000;

  if (device_param->spin_damp > 0)
  {
    if (status_ctx->devices_status == STATUS_RUNNING)
    {
      switch (kern_run)
      {
        case KERN_RUN_1:      device_param->exec_us_prev1[iterationm]      = exec_us; break;
        case KERN_RUN_2:      device_param->exec_us_prev2[iterationm]      = exec_us; break;
        case KERN_RUN_3:      device_param->exec_us_prev3[iterationm]      = exec_us; break;
        case KERN_RUN_4:      device_param->exec_us_prev4[iterationm]      = exec_us; break;
        case KERN_RUN_INIT2:  device_param->exec_us_prev_init2[iterationm] = exec_us; break;
        case KERN_RUN_LOOP2:  device_param->exec_us_prev_loop2[iterationm] = exec_us; break;
        case KERN_RUN_AUX1:   device_param->exec_us_prev_aux1[iterationm]  = exec_us; break;
        case KERN_RUN_AUX2:   device_param->exec_us_prev_aux2[iterationm]  = exec_us; break;
        case KERN_RUN_AUX3:   device_param->exec_us_prev_aux3[iterationm]  = exec_us; break;
        case KERN_RUN_AUX4:   device_param->exec_us_prev_aux4[iterationm]  = exec_us; break;
      }
    }
  }

  if (event_update)
  {
    u32 exec_pos = device_param->exec_pos;

    device_param->exec_msec[exec_pos] = exec_us / 1000;

    exec_pos++;

    if (exec_pos == EXEC_CACHE)
    {
      exec_pos = 0;
    }

    device_param->exec_pos = exec_pos;
  }

  CL_rc = hc_clReleaseEvent (hashcat_ctx, event);

  if (CL_rc == -1) return -1;

  CL_rc = hc_clFinish (hashcat_ctx, device_param->command_queue);

  if (CL_rc == -1) return -1;

  return 0;
}