#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int slow_candidates; } ;
typedef  TYPE_1__ user_options_t ;
struct TYPE_10__ {int skipped; int skipped_warning; int is_opencl; int /*<<< orphan*/ * kernel_params_amp; int /*<<< orphan*/  opencl_kernel_amp; int /*<<< orphan*/ * kernel_params_amp_buf32; int /*<<< orphan*/ * kernel_params_buf32; } ;
typedef  TYPE_2__ hc_device_param_t ;
struct TYPE_11__ {scalar_t__ attack_exec; } ;
typedef  TYPE_3__ hashconfig_t ;
struct TYPE_12__ {TYPE_1__* user_options; TYPE_6__* backend_ctx; TYPE_3__* hashconfig; TYPE_5__* combinator_ctx; } ;
typedef  TYPE_4__ hashcat_ctx_t ;
struct TYPE_13__ {int /*<<< orphan*/  combs_mode; } ;
typedef  TYPE_5__ combinator_ctx_t ;
typedef  int /*<<< orphan*/  cl_uint ;
struct TYPE_14__ {int enabled; int backend_devices_cnt; TYPE_2__* devices_param; } ;
typedef  TYPE_6__ backend_ctx_t ;

/* Variables and functions */
 scalar_t__ ATTACK_EXEC_OUTSIDE_KERNEL ; 
 int hc_clSetKernelArg (TYPE_4__*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

int backend_session_update_combinator (hashcat_ctx_t *hashcat_ctx)
{
  combinator_ctx_t *combinator_ctx = hashcat_ctx->combinator_ctx;
  hashconfig_t     *hashconfig     = hashcat_ctx->hashconfig;
  backend_ctx_t    *backend_ctx    = hashcat_ctx->backend_ctx;
  user_options_t   *user_options   = hashcat_ctx->user_options;

  if (backend_ctx->enabled == false) return 0;

  for (int backend_devices_idx = 0; backend_devices_idx < backend_ctx->backend_devices_cnt; backend_devices_idx++)
  {
    hc_device_param_t *device_param = &backend_ctx->devices_param[backend_devices_idx];

    if (device_param->skipped == true) continue;

    if (device_param->skipped_warning == true) continue;

    // kernel_params

    device_param->kernel_params_buf32[33] = combinator_ctx->combs_mode;

    /*
    if (device_param->is_opencl == true)
    {
      CL_rc = hc_clSetKernelArg (hashcat_ctx, device_param->opencl_kernel1, 33, sizeof (cl_uint), device_param->kernel_params[33]); if (CL_rc == -1) return -1;
      CL_rc = hc_clSetKernelArg (hashcat_ctx, device_param->opencl_kernel2, 33, sizeof (cl_uint), device_param->kernel_params[33]); if (CL_rc == -1) return -1;
      CL_rc = hc_clSetKernelArg (hashcat_ctx, device_param->opencl_kernel3, 33, sizeof (cl_uint), device_param->kernel_params[33]); if (CL_rc == -1) return -1;
      CL_rc = hc_clSetKernelArg (hashcat_ctx, device_param->opencl_kernel4, 33, sizeof (cl_uint), device_param->kernel_params[33]); if (CL_rc == -1) return -1;

      if (hashconfig->opts_type & OPTS_TYPE_HOOK12) { CL_rc = hc_clSetKernelArg (hashcat_ctx, device_param->opencl_kernel12,     33, sizeof (cl_uint), device_param->kernel_params[33]); if (CL_rc == -1) return -1; }
      if (hashconfig->opts_type & OPTS_TYPE_HOOK23) { CL_rc = hc_clSetKernelArg (hashcat_ctx, device_param->opencl_kernel23,     33, sizeof (cl_uint), device_param->kernel_params[33]); if (CL_rc == -1) return -1; }
      if (hashconfig->opts_type & OPTS_TYPE_INIT2)  { CL_rc = hc_clSetKernelArg (hashcat_ctx, device_param->opencl_kernel_init2, 33, sizeof (cl_uint), device_param->kernel_params[33]); if (CL_rc == -1) return -1; }
      if (hashconfig->opts_type & OPTS_TYPE_LOOP2)  { CL_rc = hc_clSetKernelArg (hashcat_ctx, device_param->opencl_kernel_loop2, 33, sizeof (cl_uint), device_param->kernel_params[33]); if (CL_rc == -1) return -1; }
    }
    */

    // kernel_params_amp

    if (user_options->slow_candidates == true)
    {
    }
    else
    {
      device_param->kernel_params_amp_buf32[5] = combinator_ctx->combs_mode;

      if (hashconfig->attack_exec == ATTACK_EXEC_OUTSIDE_KERNEL)
      {
        if (device_param->is_opencl == true)
        {
          const int rc_clSetKernelArg = hc_clSetKernelArg (hashcat_ctx, device_param->opencl_kernel_amp, 5, sizeof (cl_uint), device_param->kernel_params_amp[5]);

          if (rc_clSetKernelArg == -1) return -1;
        }
      }
    }
  }

  return 0;
}