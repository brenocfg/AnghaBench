#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ hm_nvapi; } ;
typedef  TYPE_1__ hwmon_ctx_t ;
struct TYPE_7__ {TYPE_1__* hwmon_ctx; } ;
typedef  TYPE_2__ hashcat_ctx_t ;
struct TYPE_8__ {scalar_t__ lib; } ;
typedef  TYPE_3__ NVAPI_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  hc_dlclose (scalar_t__) ; 
 int /*<<< orphan*/  hcfree (TYPE_3__*) ; 

__attribute__((used)) static void nvapi_close (hashcat_ctx_t *hashcat_ctx)
{
  hwmon_ctx_t *hwmon_ctx = hashcat_ctx->hwmon_ctx;

  NVAPI_PTR *nvapi = (NVAPI_PTR *) hwmon_ctx->hm_nvapi;

  if (nvapi)
  {
    if (nvapi->lib)
      hc_dlclose (nvapi->lib);

    hcfree (nvapi);
  }
}