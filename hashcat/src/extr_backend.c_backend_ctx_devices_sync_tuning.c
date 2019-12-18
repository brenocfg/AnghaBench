#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {int skipped; int skipped_warning; int kernel_accel; int kernel_threads; int device_processors; int hardware_power; int kernel_power; int /*<<< orphan*/  kernel_loops; } ;
typedef  TYPE_1__ hc_device_param_t ;
struct TYPE_8__ {TYPE_3__* backend_ctx; } ;
typedef  TYPE_2__ hashcat_ctx_t ;
struct TYPE_9__ {int enabled; int backend_devices_cnt; TYPE_1__* devices_param; } ;
typedef  TYPE_3__ backend_ctx_t ;

/* Variables and functions */
 int is_same_device_type (TYPE_1__*,TYPE_1__*) ; 

void backend_ctx_devices_sync_tuning (hashcat_ctx_t *hashcat_ctx)
{
  backend_ctx_t *backend_ctx = hashcat_ctx->backend_ctx;

  if (backend_ctx->enabled == false) return;

  for (int backend_devices_cnt_src = 0; backend_devices_cnt_src < backend_ctx->backend_devices_cnt; backend_devices_cnt_src++)
  {
    hc_device_param_t *device_param_src = &backend_ctx->devices_param[backend_devices_cnt_src];

    if (device_param_src->skipped == true) continue;

    if (device_param_src->skipped_warning == true) continue;

    for (int backend_devices_cnt_dst = backend_devices_cnt_src + 1; backend_devices_cnt_dst < backend_ctx->backend_devices_cnt; backend_devices_cnt_dst++)
    {
      hc_device_param_t *device_param_dst = &backend_ctx->devices_param[backend_devices_cnt_dst];

      if (device_param_dst->skipped == true) continue;

      if (device_param_dst->skipped_warning == true) continue;

      if (is_same_device_type (device_param_src, device_param_dst) == false) continue;

      device_param_dst->kernel_accel   = device_param_src->kernel_accel;
      device_param_dst->kernel_loops   = device_param_src->kernel_loops;
      device_param_dst->kernel_threads = device_param_src->kernel_threads;

      const u32 hardware_power = device_param_dst->device_processors * device_param_dst->kernel_threads;

      device_param_dst->hardware_power = hardware_power;

      const u32 kernel_power = device_param_dst->hardware_power * device_param_dst->kernel_accel;

      device_param_dst->kernel_power = kernel_power;
    }
  }
}