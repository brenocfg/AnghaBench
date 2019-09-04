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
struct TYPE_5__ {int enabled; size_t platforms_cnt; size_t devices_cnt; int need_adl; int need_nvml; int need_nvapi; int need_sysfs; scalar_t__ devices_active; TYPE_2__* devices_param; int /*<<< orphan*/ * platforms_version; int /*<<< orphan*/ * platforms_name; int /*<<< orphan*/ * platforms_vendor; } ;
typedef  TYPE_1__ opencl_ctx_t ;
struct TYPE_6__ {int skipped; int /*<<< orphan*/  device_vendor; int /*<<< orphan*/  device_opencl_version; int /*<<< orphan*/  driver_version; int /*<<< orphan*/  device_version; int /*<<< orphan*/  device_name; } ;
typedef  TYPE_2__ hc_device_param_t ;
struct TYPE_7__ {TYPE_1__* opencl_ctx; } ;
typedef  TYPE_3__ hashcat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  hcfree (int /*<<< orphan*/ ) ; 

void opencl_ctx_devices_destroy (hashcat_ctx_t *hashcat_ctx)
{
  opencl_ctx_t *opencl_ctx = hashcat_ctx->opencl_ctx;

  if (opencl_ctx->enabled == false) return;

  for (u32 platform_id = 0; platform_id < opencl_ctx->platforms_cnt; platform_id++)
  {
    hcfree (opencl_ctx->platforms_vendor[platform_id]);
    hcfree (opencl_ctx->platforms_name[platform_id]);
    hcfree (opencl_ctx->platforms_version[platform_id]);
  }

  for (u32 device_id = 0; device_id < opencl_ctx->devices_cnt; device_id++)
  {
    hc_device_param_t *device_param = &opencl_ctx->devices_param[device_id];

    if (device_param->skipped == true) continue;

    hcfree (device_param->device_name);
    hcfree (device_param->device_version);
    hcfree (device_param->driver_version);
    hcfree (device_param->device_opencl_version);
    hcfree (device_param->device_vendor);
  }

  opencl_ctx->devices_cnt    = 0;
  opencl_ctx->devices_active = 0;

  opencl_ctx->need_adl    = false;
  opencl_ctx->need_nvml   = false;
  opencl_ctx->need_nvapi  = false;
  opencl_ctx->need_sysfs  = false;
}