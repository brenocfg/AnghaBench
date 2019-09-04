#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int slow_candidates; } ;
typedef  TYPE_1__ user_options_t ;
typedef  size_t u32 ;
struct TYPE_10__ {int enabled; size_t devices_cnt; TYPE_4__* devices_param; } ;
typedef  TYPE_2__ opencl_ctx_t ;
struct TYPE_11__ {int /*<<< orphan*/  markov_css_buf; int /*<<< orphan*/  root_css_buf; int /*<<< orphan*/  css_cnt; } ;
typedef  TYPE_3__ mask_ctx_t ;
struct TYPE_12__ {int skipped; int skipped_warning; int /*<<< orphan*/  size_markov_css; int /*<<< orphan*/  d_markov_css_buf; int /*<<< orphan*/  command_queue; int /*<<< orphan*/  size_root_css; int /*<<< orphan*/  d_root_css_buf; int /*<<< orphan*/ * kernel_params_mp; int /*<<< orphan*/  kernel_mp; int /*<<< orphan*/ * kernel_params_mp_buf32; scalar_t__* kernel_params_mp_buf64; } ;
typedef  TYPE_4__ hc_device_param_t ;
struct TYPE_13__ {TYPE_1__* user_options; TYPE_2__* opencl_ctx; TYPE_3__* mask_ctx; } ;
typedef  TYPE_5__ hashcat_ctx_t ;
typedef  int /*<<< orphan*/  cl_ulong ;
typedef  int /*<<< orphan*/  cl_uint ;

/* Variables and functions */
 int CL_SUCCESS ; 
 int /*<<< orphan*/  CL_TRUE ; 
 int hc_clEnqueueWriteBuffer (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hc_clSetKernelArg (TYPE_5__*,int /*<<< orphan*/ ,size_t,int,int /*<<< orphan*/ ) ; 

int opencl_session_update_mp (hashcat_ctx_t *hashcat_ctx)
{
  mask_ctx_t     *mask_ctx     = hashcat_ctx->mask_ctx;
  opencl_ctx_t   *opencl_ctx   = hashcat_ctx->opencl_ctx;
  user_options_t *user_options = hashcat_ctx->user_options;

  if (opencl_ctx->enabled == false) return 0;

  if (user_options->slow_candidates == true) return 0;

  for (u32 device_id = 0; device_id < opencl_ctx->devices_cnt; device_id++)
  {
    hc_device_param_t *device_param = &opencl_ctx->devices_param[device_id];

    if (device_param->skipped == true) continue;

    if (device_param->skipped_warning == true) continue;

    device_param->kernel_params_mp_buf64[3] = 0;
    device_param->kernel_params_mp_buf32[4] = mask_ctx->css_cnt;

    int CL_rc = CL_SUCCESS;

    for (u32 i = 3; i < 4; i++) { CL_rc = hc_clSetKernelArg (hashcat_ctx, device_param->kernel_mp, i, sizeof (cl_ulong), device_param->kernel_params_mp[i]); if (CL_rc == -1) return -1; }
    for (u32 i = 4; i < 8; i++) { CL_rc = hc_clSetKernelArg (hashcat_ctx, device_param->kernel_mp, i, sizeof (cl_uint), device_param->kernel_params_mp[i]); if (CL_rc == -1) return -1; }

    CL_rc = hc_clEnqueueWriteBuffer (hashcat_ctx, device_param->command_queue, device_param->d_root_css_buf,   CL_TRUE, 0, device_param->size_root_css,   mask_ctx->root_css_buf,   0, NULL, NULL); if (CL_rc == -1) return -1;
    CL_rc = hc_clEnqueueWriteBuffer (hashcat_ctx, device_param->command_queue, device_param->d_markov_css_buf, CL_TRUE, 0, device_param->size_markov_css, mask_ctx->markov_css_buf, 0, NULL, NULL); if (CL_rc == -1) return -1;
  }

  return 0;
}