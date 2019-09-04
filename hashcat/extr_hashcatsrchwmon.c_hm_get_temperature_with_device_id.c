#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_15__ {TYPE_1__* devices_param; } ;
typedef  TYPE_3__ opencl_ctx_t ;
struct TYPE_16__ {int enabled; TYPE_2__* hm_device; scalar_t__ hm_nvml; scalar_t__ hm_sysfs; scalar_t__ hm_adl; } ;
typedef  TYPE_4__ hwmon_ctx_t ;
struct TYPE_17__ {TYPE_3__* opencl_ctx; TYPE_4__* hwmon_ctx; } ;
typedef  TYPE_5__ hashcat_ctx_t ;
struct TYPE_18__ {int iSize; int iTemperature; } ;
struct TYPE_14__ {int temperature_get_supported; int od_version; int /*<<< orphan*/  nvml; int /*<<< orphan*/  adl; } ;
struct TYPE_13__ {int device_type; scalar_t__ device_vendor_id; } ;
typedef  TYPE_6__ ADLTemperature ;

/* Variables and functions */
 int CL_DEVICE_TYPE_GPU ; 
 int /*<<< orphan*/  NVML_TEMPERATURE_GPU ; 
 scalar_t__ VENDOR_ID_AMD ; 
 scalar_t__ VENDOR_ID_NV ; 
 int hm_ADL_Overdrive5_Temperature_Get (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int hm_ADL_Overdrive6_Temperature_Get (TYPE_5__*,int /*<<< orphan*/ ,int*) ; 
 int hm_NVML_nvmlDeviceGetTemperature (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 int hm_SYSFS_get_temperature_current (TYPE_5__*,size_t const,int*) ; 

int hm_get_temperature_with_device_id (hashcat_ctx_t *hashcat_ctx, const u32 device_id)
{
  hwmon_ctx_t  *hwmon_ctx  = hashcat_ctx->hwmon_ctx;
  opencl_ctx_t *opencl_ctx = hashcat_ctx->opencl_ctx;

  if (hwmon_ctx->enabled == false) return -1;

  if (hwmon_ctx->hm_device[device_id].temperature_get_supported == false) return -1;

  if ((opencl_ctx->devices_param[device_id].device_type & CL_DEVICE_TYPE_GPU) == 0) return -1;

  if (opencl_ctx->devices_param[device_id].device_vendor_id == VENDOR_ID_AMD)
  {
    if (hwmon_ctx->hm_adl)
    {
      if (hwmon_ctx->hm_device[device_id].od_version == 5)
      {
        ADLTemperature Temperature;

        Temperature.iSize = sizeof (ADLTemperature);

        if (hm_ADL_Overdrive5_Temperature_Get (hashcat_ctx, hwmon_ctx->hm_device[device_id].adl, 0, &Temperature) == -1)
        {
          hwmon_ctx->hm_device[device_id].temperature_get_supported = false;

          return -1;
        }

        return Temperature.iTemperature / 1000;
      }

      if (hwmon_ctx->hm_device[device_id].od_version == 6)
      {
        int Temperature = 0;

        if (hm_ADL_Overdrive6_Temperature_Get (hashcat_ctx, hwmon_ctx->hm_device[device_id].adl, &Temperature) == -1)
        {
          hwmon_ctx->hm_device[device_id].temperature_get_supported = false;

          return -1;
        }

        return Temperature / 1000;
      }
    }

    if (hwmon_ctx->hm_sysfs)
    {
      int temperature = 0;

      if (hm_SYSFS_get_temperature_current (hashcat_ctx, device_id, &temperature) == -1)
      {
        hwmon_ctx->hm_device[device_id].temperature_get_supported = false;

        return -1;
      }

      return temperature;
    }
  }

  if (opencl_ctx->devices_param[device_id].device_vendor_id == VENDOR_ID_NV)
  {
    if (hwmon_ctx->hm_nvml)
    {
      int temperature = 0;

      if (hm_NVML_nvmlDeviceGetTemperature (hashcat_ctx, hwmon_ctx->hm_device[device_id].nvml, NVML_TEMPERATURE_GPU, (u32 *) &temperature) == -1)
      {
        hwmon_ctx->hm_device[device_id].temperature_get_supported = false;

        return -1;
      }

      return temperature;
    }
  }

  hwmon_ctx->hm_device[device_id].temperature_get_supported = false;

  return -1;
}