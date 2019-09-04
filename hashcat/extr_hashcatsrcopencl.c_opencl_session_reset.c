#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u32 ;
struct TYPE_7__ {int enabled; size_t devices_cnt; scalar_t__ kernel_power_final; scalar_t__ kernel_power_all; TYPE_3__* devices_param; } ;
typedef  TYPE_2__ opencl_ctx_t ;
struct TYPE_6__ {scalar_t__ tv_sec; } ;
struct TYPE_8__ {int skipped; int speed_only_finish; int size_pws_comp; int size_pws_idx; TYPE_1__ timer_speed; scalar_t__ words_done; scalar_t__ words_off; scalar_t__ pws_cnt; scalar_t__ pws_idx; scalar_t__ pws_comp; scalar_t__ innerloop_left; scalar_t__ innerloop_pos; scalar_t__ outerloop_left; scalar_t__ outerloop_pos; scalar_t__ outerloop_msec; scalar_t__ exec_msec; scalar_t__ exec_pos; scalar_t__ speed_msec; scalar_t__ speed_cnt; scalar_t__ speed_pos; } ;
typedef  TYPE_3__ hc_device_param_t ;
struct TYPE_9__ {TYPE_2__* opencl_ctx; } ;
typedef  TYPE_4__ hashcat_ctx_t ;

/* Variables and functions */
 int EXEC_CACHE ; 
 int SPEED_CACHE ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 

void opencl_session_reset (hashcat_ctx_t *hashcat_ctx)
{
  opencl_ctx_t *opencl_ctx = hashcat_ctx->opencl_ctx;

  if (opencl_ctx->enabled == false) return;

  for (u32 device_id = 0; device_id < opencl_ctx->devices_cnt; device_id++)
  {
    hc_device_param_t *device_param = &opencl_ctx->devices_param[device_id];

    if (device_param->skipped == true) continue;

    device_param->speed_pos = 0;

    memset (device_param->speed_cnt,  0, SPEED_CACHE * sizeof (u64));
    memset (device_param->speed_msec, 0, SPEED_CACHE * sizeof (double));

    device_param->speed_only_finish = false;

    device_param->exec_pos = 0;

    memset (device_param->exec_msec, 0, EXEC_CACHE * sizeof (double));

    device_param->outerloop_msec = 0;
    device_param->outerloop_pos  = 0;
    device_param->outerloop_left = 0;
    device_param->innerloop_pos  = 0;
    device_param->innerloop_left = 0;

    // some more resets:

    if (device_param->pws_comp) memset (device_param->pws_comp, 0, device_param->size_pws_comp);
    if (device_param->pws_idx)  memset (device_param->pws_idx,  0, device_param->size_pws_idx);

    device_param->pws_cnt = 0;

    device_param->words_off  = 0;
    device_param->words_done = 0;

    #if defined (_WIN)
    device_param->timer_speed.QuadPart = 0;
    #else
    device_param->timer_speed.tv_sec = 0;
    #endif
  }

  opencl_ctx->kernel_power_all   = 0;
  opencl_ctx->kernel_power_final = 0;
}