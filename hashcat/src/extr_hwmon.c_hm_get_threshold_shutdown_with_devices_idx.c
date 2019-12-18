#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int enabled; TYPE_2__* hm_device; scalar_t__ hm_nvml; scalar_t__ hm_adl; } ;
typedef  TYPE_3__ hwmon_ctx_t ;
struct TYPE_11__ {TYPE_5__* backend_ctx; TYPE_3__* hwmon_ctx; } ;
typedef  TYPE_4__ hashcat_ctx_t ;
struct TYPE_12__ {TYPE_1__* devices_param; } ;
typedef  TYPE_5__ backend_ctx_t ;
struct TYPE_9__ {int threshold_shutdown_get_supported; int od_version; int /*<<< orphan*/  nvml; } ;
struct TYPE_8__ {int is_cuda; int is_opencl; int opencl_device_type; scalar_t__ opencl_device_vendor_id; } ;

/* Variables and functions */
 int CL_DEVICE_TYPE_GPU ; 
 int /*<<< orphan*/  NVML_TEMPERATURE_THRESHOLD_SHUTDOWN ; 
 scalar_t__ VENDOR_ID_AMD ; 
 scalar_t__ VENDOR_ID_NV ; 
 int hm_NVML_nvmlDeviceGetTemperatureThreshold (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

int hm_get_threshold_shutdown_with_devices_idx (hashcat_ctx_t *hashcat_ctx, const int backend_device_idx)
{
  hwmon_ctx_t   *hwmon_ctx   = hashcat_ctx->hwmon_ctx;
  backend_ctx_t *backend_ctx = hashcat_ctx->backend_ctx;

  if (hwmon_ctx->enabled == false) return -1;

  if (hwmon_ctx->hm_device[backend_device_idx].threshold_shutdown_get_supported == false) return -1;

  if (backend_ctx->devices_param[backend_device_idx].is_cuda == true)
  {
    if (hwmon_ctx->hm_nvml)
    {
      int target = 0;

      if (hm_NVML_nvmlDeviceGetTemperatureThreshold (hashcat_ctx, hwmon_ctx->hm_device[backend_device_idx].nvml, NVML_TEMPERATURE_THRESHOLD_SHUTDOWN, (unsigned int *) &target) == -1)
      {
        hwmon_ctx->hm_device[backend_device_idx].threshold_shutdown_get_supported = false;

        return -1;
      }

      return target;
    }
  }

  if (backend_ctx->devices_param[backend_device_idx].is_opencl == true)
  {
    if ((backend_ctx->devices_param[backend_device_idx].opencl_device_type & CL_DEVICE_TYPE_GPU) == 0) return -1;

    if (backend_ctx->devices_param[backend_device_idx].opencl_device_vendor_id == VENDOR_ID_AMD)
    {
      if (hwmon_ctx->hm_adl)
      {
        if (hwmon_ctx->hm_device[backend_device_idx].od_version == 5)
        {

        }
        else if (hwmon_ctx->hm_device[backend_device_idx].od_version == 6)
        {

        }
      }
    }

    if (backend_ctx->devices_param[backend_device_idx].opencl_device_vendor_id == VENDOR_ID_NV)
    {
      if (hwmon_ctx->hm_nvml)
      {
        int target = 0;

        if (hm_NVML_nvmlDeviceGetTemperatureThreshold (hashcat_ctx, hwmon_ctx->hm_device[backend_device_idx].nvml, NVML_TEMPERATURE_THRESHOLD_SHUTDOWN, (unsigned int *) &target) == -1)
        {
          hwmon_ctx->hm_device[backend_device_idx].threshold_shutdown_get_supported = false;

          return -1;
        }

        return target;
      }
    }
  }

  hwmon_ctx->hm_device[backend_device_idx].threshold_shutdown_get_supported = false;

  return -1;
}