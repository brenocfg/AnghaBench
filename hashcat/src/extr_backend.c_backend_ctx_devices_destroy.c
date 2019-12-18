#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_5__ {int skipped; int is_opencl; int /*<<< orphan*/  opencl_device_vendor; int /*<<< orphan*/  opencl_device_c_version; int /*<<< orphan*/  opencl_device_version; int /*<<< orphan*/  opencl_driver_version; int /*<<< orphan*/  device_name; } ;
typedef  TYPE_1__ hc_device_param_t ;
struct TYPE_6__ {TYPE_3__* backend_ctx; } ;
typedef  TYPE_2__ hashcat_ctx_t ;
struct TYPE_7__ {int enabled; size_t opencl_platforms_cnt; int backend_devices_cnt; int need_adl; int need_nvml; int need_nvapi; int need_sysfs; scalar_t__ opencl_devices_active; scalar_t__ opencl_devices_cnt; scalar_t__ cuda_devices_active; scalar_t__ cuda_devices_cnt; scalar_t__ backend_devices_active; TYPE_1__* devices_param; int /*<<< orphan*/ * opencl_platforms_version; int /*<<< orphan*/ * opencl_platforms_vendor; int /*<<< orphan*/ * opencl_platforms_name; int /*<<< orphan*/ * opencl_platforms_devices; } ;
typedef  TYPE_3__ backend_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  hcfree (int /*<<< orphan*/ ) ; 

void backend_ctx_devices_destroy (hashcat_ctx_t *hashcat_ctx)
{
  backend_ctx_t *backend_ctx = hashcat_ctx->backend_ctx;

  if (backend_ctx->enabled == false) return;

  for (u32 opencl_platforms_idx = 0; opencl_platforms_idx < backend_ctx->opencl_platforms_cnt; opencl_platforms_idx++)
  {
    hcfree (backend_ctx->opencl_platforms_devices[opencl_platforms_idx]);
    hcfree (backend_ctx->opencl_platforms_name[opencl_platforms_idx]);
    hcfree (backend_ctx->opencl_platforms_vendor[opencl_platforms_idx]);
    hcfree (backend_ctx->opencl_platforms_version[opencl_platforms_idx]);
  }

  for (int backend_devices_idx = 0; backend_devices_idx < backend_ctx->backend_devices_cnt; backend_devices_idx++)
  {
    hc_device_param_t *device_param = &backend_ctx->devices_param[backend_devices_idx];

    if (device_param->skipped == true) continue;

    hcfree (device_param->device_name);

    if (device_param->is_opencl == true)
    {
      hcfree (device_param->opencl_driver_version);
      hcfree (device_param->opencl_device_version);
      hcfree (device_param->opencl_device_c_version);
      hcfree (device_param->opencl_device_vendor);
    }
  }

  backend_ctx->backend_devices_cnt    = 0;
  backend_ctx->backend_devices_active = 0;
  backend_ctx->cuda_devices_cnt       = 0;
  backend_ctx->cuda_devices_active    = 0;
  backend_ctx->opencl_devices_cnt     = 0;
  backend_ctx->opencl_devices_active  = 0;

  backend_ctx->need_adl    = false;
  backend_ctx->need_nvml   = false;
  backend_ctx->need_nvapi  = false;
  backend_ctx->need_sysfs  = false;
}