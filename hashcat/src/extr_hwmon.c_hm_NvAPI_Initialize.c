#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ hm_nvapi; } ;
typedef  TYPE_1__ hwmon_ctx_t ;
struct TYPE_11__ {TYPE_1__* hwmon_ctx; } ;
typedef  TYPE_2__ hashcat_ctx_t ;
struct TYPE_13__ {int /*<<< orphan*/  (* NvAPI_Initialize ) () ;} ;
struct TYPE_12__ {int /*<<< orphan*/  member_0; } ;
typedef  scalar_t__ NvAPI_Status ;
typedef  TYPE_3__ NvAPI_ShortString ;
typedef  TYPE_4__ NVAPI_PTR ;

/* Variables and functions */
 scalar_t__ const NVAPI_LIBRARY_NOT_FOUND ; 
 scalar_t__ const NVAPI_OK ; 
 int /*<<< orphan*/  event_log_error (TYPE_2__*,char*,TYPE_3__) ; 
 int /*<<< orphan*/  hm_NvAPI_GetErrorMessage (TYPE_4__*,scalar_t__ const,TYPE_3__) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static int hm_NvAPI_Initialize (hashcat_ctx_t *hashcat_ctx)
{
  hwmon_ctx_t *hwmon_ctx = hashcat_ctx->hwmon_ctx;

  NVAPI_PTR *nvapi = (NVAPI_PTR *) hwmon_ctx->hm_nvapi;

  const NvAPI_Status NvAPI_rc = (NvAPI_Status) nvapi->NvAPI_Initialize ();

  if (NvAPI_rc == NVAPI_LIBRARY_NOT_FOUND) return -1;

  if (NvAPI_rc != NVAPI_OK)
  {
    NvAPI_ShortString string = { 0 };

    hm_NvAPI_GetErrorMessage (nvapi, NvAPI_rc, string);

    event_log_error (hashcat_ctx, "NvAPI_Initialize(): %s", string);

    return -1;
  }

  return 0;
}