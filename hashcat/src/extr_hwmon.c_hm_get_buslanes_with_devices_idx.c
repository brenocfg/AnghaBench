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
struct TYPE_14__ {int enabled; TYPE_2__* hm_device; scalar_t__ hm_nvml; scalar_t__ hm_sysfs; scalar_t__ hm_adl; } ;
typedef  TYPE_3__ hwmon_ctx_t ;
struct TYPE_15__ {TYPE_5__* backend_ctx; TYPE_3__* hwmon_ctx; } ;
typedef  TYPE_4__ hashcat_ctx_t ;
struct TYPE_16__ {TYPE_1__* devices_param; } ;
typedef  TYPE_5__ backend_ctx_t ;
struct TYPE_17__ {int iSize; int iCurrentBusLanes; } ;
struct TYPE_13__ {int buslanes_get_supported; int /*<<< orphan*/  nvml; int /*<<< orphan*/  adl; } ;
struct TYPE_12__ {int is_cuda; int is_opencl; int opencl_device_type; scalar_t__ opencl_device_vendor_id; } ;
typedef  TYPE_6__ ADLPMActivity ;

/* Variables and functions */
 int CL_DEVICE_TYPE_GPU ; 
 scalar_t__ VENDOR_ID_AMD ; 
 scalar_t__ VENDOR_ID_NV ; 
 int hm_ADL_Overdrive_CurrentActivity_Get (TYPE_4__*,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int hm_NVML_nvmlDeviceGetCurrPcieLinkWidth (TYPE_4__*,int /*<<< orphan*/ ,unsigned int*) ; 
 int hm_SYSFS_get_pp_dpm_pcie (TYPE_4__*,int const,int*) ; 

int hm_get_buslanes_with_devices_idx (hashcat_ctx_t *hashcat_ctx, const int backend_device_idx)
{
  hwmon_ctx_t   *hwmon_ctx   = hashcat_ctx->hwmon_ctx;
  backend_ctx_t *backend_ctx = hashcat_ctx->backend_ctx;

  if (hwmon_ctx->enabled == false) return -1;

  if (hwmon_ctx->hm_device[backend_device_idx].buslanes_get_supported == false) return -1;

  if (backend_ctx->devices_param[backend_device_idx].is_cuda == true)
  {
    if (hwmon_ctx->hm_nvml)
    {
      unsigned int currLinkWidth;

      if (hm_NVML_nvmlDeviceGetCurrPcieLinkWidth (hashcat_ctx, hwmon_ctx->hm_device[backend_device_idx].nvml, &currLinkWidth) == -1)
      {
        hwmon_ctx->hm_device[backend_device_idx].buslanes_get_supported = false;

        return -1;
      }

      return currLinkWidth;
    }
  }

  if (backend_ctx->devices_param[backend_device_idx].is_opencl == true)
  {
    if ((backend_ctx->devices_param[backend_device_idx].opencl_device_type & CL_DEVICE_TYPE_GPU) == 0) return -1;

    if (backend_ctx->devices_param[backend_device_idx].opencl_device_vendor_id == VENDOR_ID_AMD)
    {
      if (hwmon_ctx->hm_adl)
      {
        ADLPMActivity PMActivity;

        PMActivity.iSize = sizeof (ADLPMActivity);

        if (hm_ADL_Overdrive_CurrentActivity_Get (hashcat_ctx, hwmon_ctx->hm_device[backend_device_idx].adl, &PMActivity) == -1)
        {
          hwmon_ctx->hm_device[backend_device_idx].buslanes_get_supported = false;

          return -1;
        }

        return PMActivity.iCurrentBusLanes;
      }

      if (hwmon_ctx->hm_sysfs)
      {
        int lanes;

        if (hm_SYSFS_get_pp_dpm_pcie (hashcat_ctx, backend_device_idx, &lanes) == -1)
        {
          hwmon_ctx->hm_device[backend_device_idx].buslanes_get_supported = false;

          return -1;
        }

        return lanes;
      }
    }

    if (backend_ctx->devices_param[backend_device_idx].opencl_device_vendor_id == VENDOR_ID_NV)
    {
      if (hwmon_ctx->hm_nvml)
      {
        unsigned int currLinkWidth;

        if (hm_NVML_nvmlDeviceGetCurrPcieLinkWidth (hashcat_ctx, hwmon_ctx->hm_device[backend_device_idx].nvml, &currLinkWidth) == -1)
        {
          hwmon_ctx->hm_device[backend_device_idx].buslanes_get_supported = false;

          return -1;
        }

        return currLinkWidth;
      }
    }
  }

  hwmon_ctx->hm_device[backend_device_idx].buslanes_get_supported = false;

  return -1;
}