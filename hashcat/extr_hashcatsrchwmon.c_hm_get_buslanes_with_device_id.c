#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_14__ {TYPE_1__* devices_param; } ;
typedef  TYPE_3__ opencl_ctx_t ;
struct TYPE_15__ {int enabled; TYPE_2__* hm_device; scalar_t__ hm_nvml; scalar_t__ hm_sysfs; scalar_t__ hm_adl; } ;
typedef  TYPE_4__ hwmon_ctx_t ;
struct TYPE_16__ {TYPE_3__* opencl_ctx; TYPE_4__* hwmon_ctx; } ;
typedef  TYPE_5__ hashcat_ctx_t ;
struct TYPE_17__ {int iSize; int iCurrentBusLanes; } ;
struct TYPE_13__ {int buslanes_get_supported; int /*<<< orphan*/  nvml; int /*<<< orphan*/  adl; } ;
struct TYPE_12__ {int device_type; scalar_t__ device_vendor_id; } ;
typedef  TYPE_6__ ADLPMActivity ;

/* Variables and functions */
 int CL_DEVICE_TYPE_GPU ; 
 scalar_t__ VENDOR_ID_AMD ; 
 scalar_t__ VENDOR_ID_NV ; 
 int hm_ADL_Overdrive_CurrentActivity_Get (TYPE_5__*,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int hm_NVML_nvmlDeviceGetCurrPcieLinkWidth (TYPE_5__*,int /*<<< orphan*/ ,unsigned int*) ; 
 int hm_SYSFS_get_pp_dpm_pcie (TYPE_5__*,size_t const,int*) ; 

int hm_get_buslanes_with_device_id (hashcat_ctx_t *hashcat_ctx, const u32 device_id)
{
  hwmon_ctx_t  *hwmon_ctx  = hashcat_ctx->hwmon_ctx;
  opencl_ctx_t *opencl_ctx = hashcat_ctx->opencl_ctx;

  if (hwmon_ctx->enabled == false) return -1;

  if (hwmon_ctx->hm_device[device_id].buslanes_get_supported == false) return -1;

  if ((opencl_ctx->devices_param[device_id].device_type & CL_DEVICE_TYPE_GPU) == 0) return -1;

  if (opencl_ctx->devices_param[device_id].device_vendor_id == VENDOR_ID_AMD)
  {
    if (hwmon_ctx->hm_adl)
    {
      ADLPMActivity PMActivity;

      PMActivity.iSize = sizeof (ADLPMActivity);

      if (hm_ADL_Overdrive_CurrentActivity_Get (hashcat_ctx, hwmon_ctx->hm_device[device_id].adl, &PMActivity) == -1)
      {
        hwmon_ctx->hm_device[device_id].buslanes_get_supported = false;

        return -1;
      }

      return PMActivity.iCurrentBusLanes;
    }

    if (hwmon_ctx->hm_sysfs)
    {
      int lanes;

      if (hm_SYSFS_get_pp_dpm_pcie (hashcat_ctx, device_id, &lanes) == -1)
      {
        hwmon_ctx->hm_device[device_id].buslanes_get_supported = false;

        return -1;
      }

      return lanes;
    }
  }

  if (opencl_ctx->devices_param[device_id].device_vendor_id == VENDOR_ID_NV)
  {
    if (hwmon_ctx->hm_nvml)
    {
      unsigned int currLinkWidth;

      if (hm_NVML_nvmlDeviceGetCurrPcieLinkWidth (hashcat_ctx, hwmon_ctx->hm_device[device_id].nvml, &currLinkWidth) == -1)
      {
        hwmon_ctx->hm_device[device_id].buslanes_get_supported = false;

        return -1;
      }

      return currLinkWidth;
    }
  }

  hwmon_ctx->hm_device[device_id].buslanes_get_supported = false;

  return -1;
}