#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ nvmlReturn_t ;
typedef  int /*<<< orphan*/  nvmlDevice_t ;
struct TYPE_7__ {scalar_t__ hm_nvml; } ;
typedef  TYPE_1__ hwmon_ctx_t ;
struct TYPE_8__ {TYPE_1__* hwmon_ctx; } ;
typedef  TYPE_2__ hashcat_ctx_t ;
struct TYPE_9__ {scalar_t__ (* nvmlDeviceGetCurrPcieLinkWidth ) (int /*<<< orphan*/ ,unsigned int*) ;} ;
typedef  TYPE_3__ NVML_PTR ;

/* Variables and functions */
 scalar_t__ const NVML_SUCCESS ; 
 int /*<<< orphan*/  event_log_error (TYPE_2__*,char*,char const*) ; 
 char* hm_NVML_nvmlErrorString (TYPE_3__*,scalar_t__ const) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int hm_NVML_nvmlDeviceGetCurrPcieLinkWidth (hashcat_ctx_t *hashcat_ctx, nvmlDevice_t device, unsigned int *currLinkWidth)
{
  hwmon_ctx_t *hwmon_ctx = hashcat_ctx->hwmon_ctx;

  NVML_PTR *nvml = (NVML_PTR *) hwmon_ctx->hm_nvml;

  const nvmlReturn_t nvml_rc = nvml->nvmlDeviceGetCurrPcieLinkWidth (device, currLinkWidth);

  if (nvml_rc != NVML_SUCCESS)
  {
    const char *string = hm_NVML_nvmlErrorString (nvml, nvml_rc);

    event_log_error (hashcat_ctx, "nvmlDeviceGetCurrPcieLinkWidth(): %s", string);

    return -1;
  }

  return 0;
}