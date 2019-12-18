#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lpFanSpeedValue ;
struct TYPE_13__ {int enabled; TYPE_2__* hm_device; scalar_t__ hm_sysfs; scalar_t__ hm_adl; } ;
typedef  TYPE_3__ hwmon_ctx_t ;
struct TYPE_14__ {TYPE_5__* backend_ctx; TYPE_3__* hwmon_ctx; } ;
typedef  TYPE_4__ hashcat_ctx_t ;
struct TYPE_15__ {TYPE_1__* devices_param; } ;
typedef  TYPE_5__ backend_ctx_t ;
struct TYPE_16__ {int iSize; int iFanSpeed; int /*<<< orphan*/  iSpeedType; } ;
struct TYPE_12__ {int fanpolicy_get_supported; int od_version; int fanspeed_get_supported; int /*<<< orphan*/  adl; } ;
struct TYPE_11__ {int is_cuda; int is_opencl; int opencl_device_type; scalar_t__ opencl_device_vendor_id; } ;
typedef  TYPE_6__ ADLFanSpeedValue ;

/* Variables and functions */
 int ADL_DL_FANCTRL_FLAG_USER_DEFINED_SPEED ; 
 int /*<<< orphan*/  ADL_DL_FANCTRL_SPEED_TYPE_PERCENT ; 
 int CL_DEVICE_TYPE_GPU ; 
 scalar_t__ VENDOR_ID_AMD ; 
 scalar_t__ VENDOR_ID_NV ; 
 int hm_ADL_Overdrive5_FanSpeed_Get (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 

int hm_get_fanpolicy_with_devices_idx (hashcat_ctx_t *hashcat_ctx, const int backend_device_idx)
{
  hwmon_ctx_t   *hwmon_ctx   = hashcat_ctx->hwmon_ctx;
  backend_ctx_t *backend_ctx = hashcat_ctx->backend_ctx;

  if (hwmon_ctx->enabled == false) return -1;

  if (hwmon_ctx->hm_device[backend_device_idx].fanpolicy_get_supported == false) return -1;

  if (backend_ctx->devices_param[backend_device_idx].is_cuda == true)
  {
    return 1;
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

          if (hm_ADL_Overdrive5_FanSpeed_Get (hashcat_ctx, hwmon_ctx->hm_device[backend_device_idx].adl, 0, &lpFanSpeedValue) == -1)
          {
            hwmon_ctx->hm_device[backend_device_idx].fanpolicy_get_supported = false;
            hwmon_ctx->hm_device[backend_device_idx].fanspeed_get_supported  = false;

            return -1;
          }

          return (lpFanSpeedValue.iFanSpeed & ADL_DL_FANCTRL_FLAG_USER_DEFINED_SPEED) ? 0 : 1;
        }

        if (hwmon_ctx->hm_device[backend_device_idx].od_version == 6)
        {
          return 1;
        }
      }

      if (hwmon_ctx->hm_sysfs)
      {
        return 1;
      }
    }

    if (backend_ctx->devices_param[backend_device_idx].opencl_device_vendor_id == VENDOR_ID_NV)
    {
      return 1;
    }
  }

  hwmon_ctx->hm_device[backend_device_idx].fanpolicy_get_supported = false;
  hwmon_ctx->hm_device[backend_device_idx].fanspeed_get_supported  = false;

  return -1;
}