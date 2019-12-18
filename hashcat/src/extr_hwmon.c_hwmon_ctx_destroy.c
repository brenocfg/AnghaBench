#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int enabled; int /*<<< orphan*/  hm_device; int /*<<< orphan*/  od_clock_mem_status; scalar_t__ hm_sysfs; scalar_t__ hm_adl; scalar_t__ hm_nvapi; scalar_t__ hm_nvml; } ;
typedef  TYPE_1__ hwmon_ctx_t ;
struct TYPE_13__ {TYPE_1__* hwmon_ctx; } ;
typedef  TYPE_2__ hashcat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  adl_close (TYPE_2__*) ; 
 int /*<<< orphan*/  hcfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hm_ADL_Main_Control_Destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  hm_NVML_nvmlShutdown (TYPE_2__*) ; 
 int /*<<< orphan*/  hm_NvAPI_Unload (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvapi_close (TYPE_2__*) ; 
 int /*<<< orphan*/  nvml_close (TYPE_2__*) ; 
 int /*<<< orphan*/  sysfs_close (TYPE_2__*) ; 

void hwmon_ctx_destroy (hashcat_ctx_t *hashcat_ctx)
{
  hwmon_ctx_t *hwmon_ctx = hashcat_ctx->hwmon_ctx;

  if (hwmon_ctx->enabled == false) return;

  // unload shared libraries

  if (hwmon_ctx->hm_nvml)
  {
    hm_NVML_nvmlShutdown (hashcat_ctx);

    nvml_close (hashcat_ctx);
  }

  if (hwmon_ctx->hm_nvapi)
  {
    hm_NvAPI_Unload (hashcat_ctx);

    nvapi_close (hashcat_ctx);
  }

  if (hwmon_ctx->hm_adl)
  {
    hm_ADL_Main_Control_Destroy (hashcat_ctx);

    adl_close (hashcat_ctx);
  }

  if (hwmon_ctx->hm_sysfs)
  {

    sysfs_close (hashcat_ctx);
  }

  // free memory

  hcfree (hwmon_ctx->od_clock_mem_status);

  hcfree (hwmon_ctx->hm_device);

  memset (hwmon_ctx, 0, sizeof (hwmon_ctx_t));
}