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
struct TYPE_7__ {int skipped; int skipped_warning; size_t device_id_alias_cnt; int is_opencl; int /*<<< orphan*/  device_id; int /*<<< orphan*/ * device_id_alias_buf; } ;
typedef  TYPE_1__ hc_device_param_t ;
struct TYPE_8__ {TYPE_3__* backend_ctx; } ;
typedef  TYPE_2__ hashcat_ctx_t ;
struct TYPE_9__ {int backend_devices_cnt; int /*<<< orphan*/  backend_devices_active; int /*<<< orphan*/  opencl_devices_active; TYPE_1__* devices_param; } ;
typedef  TYPE_3__ backend_ctx_t ;

/* Variables and functions */
 int is_same_device (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static int backend_ctx_find_alias_devices (hashcat_ctx_t *hashcat_ctx)
{
  backend_ctx_t *backend_ctx = hashcat_ctx->backend_ctx;

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

      if (is_same_device (device_param_src, device_param_dst) == false) continue;

      device_param_src->device_id_alias_buf[device_param_src->device_id_alias_cnt] = device_param_dst->device_id;
      device_param_src->device_id_alias_cnt++;

      device_param_dst->device_id_alias_buf[device_param_dst->device_id_alias_cnt] = device_param_src->device_id;
      device_param_dst->device_id_alias_cnt++;

      if (device_param_dst->is_opencl == true)
      {
        if (device_param_dst->skipped == false)
        {
          device_param_dst->skipped = true;

          backend_ctx->opencl_devices_active--;

          backend_ctx->backend_devices_active--;
        }
      }
    }
  }

  return -1;
}