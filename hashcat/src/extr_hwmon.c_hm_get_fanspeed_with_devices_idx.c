#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  lpFanSpeedValue ;
struct TYPE_18__ {int enabled; TYPE_2__* hm_device; scalar_t__ hm_nvml; scalar_t__ hm_sysfs; scalar_t__ hm_adl; } ;
typedef  TYPE_3__ hwmon_ctx_t ;
struct TYPE_19__ {TYPE_5__* backend_ctx; TYPE_3__* hwmon_ctx; } ;
typedef  TYPE_4__ hashcat_ctx_t ;
typedef  int /*<<< orphan*/  faninfo ;
struct TYPE_20__ {TYPE_1__* devices_param; } ;
typedef  TYPE_5__ backend_ctx_t ;
struct TYPE_21__ {int iSize; int iFanSpeed; int iFanSpeedPercent; int /*<<< orphan*/  iFlags; int /*<<< orphan*/  iSpeedType; } ;
struct TYPE_17__ {int fanspeed_get_supported; int od_version; int /*<<< orphan*/  nvml; int /*<<< orphan*/  adl; } ;
struct TYPE_16__ {int is_cuda; int is_opencl; int opencl_device_type; scalar_t__ opencl_device_vendor_id; } ;
typedef  TYPE_6__ ADLOD6FanSpeedInfo ;
typedef  TYPE_6__ ADLFanSpeedValue ;

/* Variables and functions */
 int /*<<< orphan*/  ADL_DL_FANCTRL_FLAG_USER_DEFINED_SPEED ; 
 int /*<<< orphan*/  ADL_DL_FANCTRL_SPEED_TYPE_PERCENT ; 
 int CL_DEVICE_TYPE_GPU ; 
 scalar_t__ VENDOR_ID_AMD ; 
 scalar_t__ VENDOR_ID_NV ; 
 int hm_ADL_Overdrive5_FanSpeed_Get (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int hm_ADL_Overdrive6_FanSpeed_Get (TYPE_4__*,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int hm_NVML_nvmlDeviceGetFanSpeed (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hm_SYSFS_get_fan_speed_current (TYPE_4__*,int const,int*) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 

int hm_get_fanspeed_with_devices_idx (hashcat_ctx_t *hashcat_ctx, const int backend_device_idx)
{
  hwmon_ctx_t   *hwmon_ctx   = hashcat_ctx->hwmon_ctx;
  backend_ctx_t *backend_ctx = hashcat_ctx->backend_ctx;

  if (hwmon_ctx->enabled == false) return -1;

  if (hwmon_ctx->hm_device[backend_device_idx].fanspeed_get_supported == false) return -1;

  if (backend_ctx->devices_param[backend_device_idx].is_cuda == true)
  {
    if (hwmon_ctx->hm_nvml)
    {
      int speed = 0;

      if (hm_NVML_nvmlDeviceGetFanSpeed (hashcat_ctx, hwmon_ctx->hm_device[backend_device_idx].nvml, (u32 *) &speed) == -1)
      {
        hwmon_ctx->hm_device[backend_device_idx].fanspeed_get_supported = false;

        return -1;
      }

      return speed;
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
          ADLFanSpeedValue lpFanSpeedValue;

          memset (&lpFanSpeedValue, 0, sizeof (lpFanSpeedValue));

          lpFanSpeedValue.iSize      = sizeof (lpFanSpeedValue);
          lpFanSpeedValue.iSpeedType = ADL_DL_FANCTRL_SPEED_TYPE_PERCENT;
          lpFanSpeedValue.iFlags     = ADL_DL_FANCTRL_FLAG_USER_DEFINED_SPEED;

          if (hm_ADL_Overdrive5_FanSpeed_Get (hashcat_ctx, hwmon_ctx->hm_device[backend_device_idx].adl, 0, &lpFanSpeedValue) == -1)
          {
            hwmon_ctx->hm_device[backend_device_idx].fanspeed_get_supported = false;

            return -1;
          }

          return lpFanSpeedValue.iFanSpeed;
        }

        if (hwmon_ctx->hm_device[backend_device_idx].od_version == 6)
        {
          ADLOD6FanSpeedInfo faninfo;

          memset (&faninfo, 0, sizeof (faninfo));

          if (hm_ADL_Overdrive6_FanSpeed_Get (hashcat_ctx, hwmon_ctx->hm_device[backend_device_idx].adl, &faninfo) == -1)
          {
            hwmon_ctx->hm_device[backend_device_idx].fanspeed_get_supported = false;

            return -1;
          }

          return faninfo.iFanSpeedPercent;
        }
      }

      if (hwmon_ctx->hm_sysfs)
      {
        int speed = 0;

        if (hm_SYSFS_get_fan_speed_current (hashcat_ctx, backend_device_idx, &speed) == -1)
        {
          hwmon_ctx->hm_device[backend_device_idx].fanspeed_get_supported = false;

          return -1;
        }

        return speed;
      }
    }

    if (backend_ctx->devices_param[backend_device_idx].opencl_device_vendor_id == VENDOR_ID_NV)
    {
      if (hwmon_ctx->hm_nvml)
      {
        int speed = 0;

        if (hm_NVML_nvmlDeviceGetFanSpeed (hashcat_ctx, hwmon_ctx->hm_device[backend_device_idx].nvml, (u32 *) &speed) == -1)
        {
          hwmon_ctx->hm_device[backend_device_idx].fanspeed_get_supported = false;

          return -1;
        }

        return speed;
      }
    }
  }

  hwmon_ctx->hm_device[backend_device_idx].fanspeed_get_supported = false;

  return -1;
}