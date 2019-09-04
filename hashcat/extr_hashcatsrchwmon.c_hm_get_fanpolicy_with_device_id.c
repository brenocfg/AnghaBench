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
typedef  size_t u32 ;
struct TYPE_13__ {TYPE_1__* devices_param; } ;
typedef  TYPE_3__ opencl_ctx_t ;
typedef  int /*<<< orphan*/  lpFanSpeedValue ;
struct TYPE_14__ {int enabled; TYPE_2__* hm_device; scalar_t__ hm_sysfs; scalar_t__ hm_adl; } ;
typedef  TYPE_4__ hwmon_ctx_t ;
struct TYPE_15__ {TYPE_3__* opencl_ctx; TYPE_4__* hwmon_ctx; } ;
typedef  TYPE_5__ hashcat_ctx_t ;
struct TYPE_16__ {int iSize; int iFanSpeed; int /*<<< orphan*/  iSpeedType; } ;
struct TYPE_12__ {int fanpolicy_get_supported; int od_version; int fanspeed_get_supported; int /*<<< orphan*/  adl; } ;
struct TYPE_11__ {int device_type; scalar_t__ device_vendor_id; } ;
typedef  TYPE_6__ ADLFanSpeedValue ;

/* Variables and functions */
 int ADL_DL_FANCTRL_FLAG_USER_DEFINED_SPEED ; 
 int /*<<< orphan*/  ADL_DL_FANCTRL_SPEED_TYPE_PERCENT ; 
 int CL_DEVICE_TYPE_GPU ; 
 scalar_t__ VENDOR_ID_AMD ; 
 scalar_t__ VENDOR_ID_NV ; 
 int hm_ADL_Overdrive5_FanSpeed_Get (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 

int hm_get_fanpolicy_with_device_id (hashcat_ctx_t *hashcat_ctx, const u32 device_id)
{
  hwmon_ctx_t  *hwmon_ctx  = hashcat_ctx->hwmon_ctx;
  opencl_ctx_t *opencl_ctx = hashcat_ctx->opencl_ctx;

  if (hwmon_ctx->enabled == false) return -1;

  if (hwmon_ctx->hm_device[device_id].fanpolicy_get_supported == false) return -1;

  if ((opencl_ctx->devices_param[device_id].device_type & CL_DEVICE_TYPE_GPU) == 0) return -1;

  if (opencl_ctx->devices_param[device_id].device_vendor_id == VENDOR_ID_AMD)
  {
    if (hwmon_ctx->hm_adl)
    {
      if (hwmon_ctx->hm_device[device_id].od_version == 5)
      {
        ADLFanSpeedValue lpFanSpeedValue;

        memset (&lpFanSpeedValue, 0, sizeof (lpFanSpeedValue));

        lpFanSpeedValue.iSize      = sizeof (lpFanSpeedValue);
        lpFanSpeedValue.iSpeedType = ADL_DL_FANCTRL_SPEED_TYPE_PERCENT;

        if (hm_ADL_Overdrive5_FanSpeed_Get (hashcat_ctx, hwmon_ctx->hm_device[device_id].adl, 0, &lpFanSpeedValue) == -1)
        {
          hwmon_ctx->hm_device[device_id].fanpolicy_get_supported = false;
          hwmon_ctx->hm_device[device_id].fanspeed_get_supported  = false;

          return -1;
        }

        return (lpFanSpeedValue.iFanSpeed & ADL_DL_FANCTRL_FLAG_USER_DEFINED_SPEED) ? 0 : 1;
      }

      if (hwmon_ctx->hm_device[device_id].od_version == 6)
      {
        return 1;
      }
    }

    if (hwmon_ctx->hm_sysfs)
    {
      return 1;
    }
  }

  if (opencl_ctx->devices_param[device_id].device_vendor_id == VENDOR_ID_NV)
  {
    return 1;
  }

  hwmon_ctx->hm_device[device_id].fanpolicy_get_supported = false;
  hwmon_ctx->hm_device[device_id].fanspeed_get_supported  = false;

  return -1;
}