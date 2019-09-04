#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
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
struct TYPE_16__ {int gpu; } ;
typedef  TYPE_4__ nvmlUtilization_t ;
struct TYPE_17__ {int enabled; TYPE_2__* hm_device; scalar_t__ hm_nvml; scalar_t__ hm_adl; } ;
typedef  TYPE_5__ hwmon_ctx_t ;
struct TYPE_18__ {TYPE_3__* opencl_ctx; TYPE_5__* hwmon_ctx; } ;
typedef  TYPE_6__ hashcat_ctx_t ;
struct TYPE_19__ {int iSize; int iActivityPercent; } ;
struct TYPE_14__ {int utilization_get_supported; int /*<<< orphan*/  nvml; int /*<<< orphan*/  adl; } ;
struct TYPE_13__ {int device_type; scalar_t__ device_vendor_id; } ;
typedef  TYPE_7__ ADLPMActivity ;

/* Variables and functions */
 int CL_DEVICE_TYPE_GPU ; 
 scalar_t__ VENDOR_ID_AMD ; 
 scalar_t__ VENDOR_ID_NV ; 
 int hm_ADL_Overdrive_CurrentActivity_Get (TYPE_6__*,int /*<<< orphan*/ ,TYPE_7__*) ; 
 int hm_NVML_nvmlDeviceGetUtilizationRates (TYPE_6__*,int /*<<< orphan*/ ,TYPE_4__*) ; 

int hm_get_utilization_with_device_id (hashcat_ctx_t *hashcat_ctx, const u32 device_id)
{
  hwmon_ctx_t  *hwmon_ctx  = hashcat_ctx->hwmon_ctx;
  opencl_ctx_t *opencl_ctx = hashcat_ctx->opencl_ctx;

  if (hwmon_ctx->enabled == false) return -1;

  if (hwmon_ctx->hm_device[device_id].utilization_get_supported == false) return -1;

  if ((opencl_ctx->devices_param[device_id].device_type & CL_DEVICE_TYPE_GPU) == 0) return -1;

  if (opencl_ctx->devices_param[device_id].device_vendor_id == VENDOR_ID_AMD)
  {
    if (hwmon_ctx->hm_adl)
    {
      ADLPMActivity PMActivity;

      PMActivity.iSize = sizeof (ADLPMActivity);

      if (hm_ADL_Overdrive_CurrentActivity_Get (hashcat_ctx, hwmon_ctx->hm_device[device_id].adl, &PMActivity) == -1)
      {
        hwmon_ctx->hm_device[device_id].utilization_get_supported = false;

        return -1;
      }

      return PMActivity.iActivityPercent;
    }
  }

  if (opencl_ctx->devices_param[device_id].device_vendor_id == VENDOR_ID_NV)
  {
    if (hwmon_ctx->hm_nvml)
    {
      nvmlUtilization_t utilization;

      if (hm_NVML_nvmlDeviceGetUtilizationRates (hashcat_ctx, hwmon_ctx->hm_device[device_id].nvml, &utilization) == -1)
      {
        hwmon_ctx->hm_device[device_id].utilization_get_supported = false;

        return -1;
      }

      return utilization.gpu;
    }
  }

  hwmon_ctx->hm_device[device_id].utilization_get_supported = false;

  return -1;
}