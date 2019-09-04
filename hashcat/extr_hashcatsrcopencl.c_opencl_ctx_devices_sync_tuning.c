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
typedef  size_t u32 ;
struct TYPE_7__ {int enabled; size_t devices_cnt; TYPE_2__* devices_param; } ;
typedef  TYPE_1__ opencl_ctx_t ;
struct TYPE_8__ {int skipped; int skipped_warning; size_t kernel_accel; size_t kernel_threads; size_t device_processors; size_t hardware_power; size_t kernel_power; int /*<<< orphan*/  kernel_loops; } ;
typedef  TYPE_2__ hc_device_param_t ;
struct TYPE_9__ {TYPE_1__* opencl_ctx; } ;
typedef  TYPE_3__ hashcat_ctx_t ;

/* Variables and functions */
 int is_same_device_type (TYPE_2__*,TYPE_2__*) ; 

void opencl_ctx_devices_sync_tuning (hashcat_ctx_t *hashcat_ctx)
{
  opencl_ctx_t *opencl_ctx = hashcat_ctx->opencl_ctx;

  if (opencl_ctx->enabled == false) return;

  for (u32 device_id_src = 0; device_id_src < opencl_ctx->devices_cnt; device_id_src++)
  {
    hc_device_param_t *device_param_src = &opencl_ctx->devices_param[device_id_src];

    if (device_param_src->skipped == true) continue;

    if (device_param_src->skipped_warning == true) continue;

    for (u32 device_id_dst = device_id_src; device_id_dst < opencl_ctx->devices_cnt; device_id_dst++)
    {
      hc_device_param_t *device_param_dst = &opencl_ctx->devices_param[device_id_dst];

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