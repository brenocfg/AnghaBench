#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ hm_nvapi; } ;
typedef  TYPE_1__ hwmon_ctx_t ;
struct TYPE_9__ {TYPE_1__* hwmon_ctx; } ;
typedef  TYPE_2__ hashcat_ctx_t ;
struct TYPE_10__ {void* lib; } ;
typedef  TYPE_3__ NVAPI_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  HC_LOAD_ADDR (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HC_LOAD_FUNC (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVAPI ; 
 int /*<<< orphan*/  NVAPI_ENUMPHYSICALGPUS ; 
 int /*<<< orphan*/  NVAPI_GETERRORMESSAGE ; 
 int /*<<< orphan*/  NVAPI_GPU_GETBUSID ; 
 int /*<<< orphan*/  NVAPI_GPU_GETBUSSLOTID ; 
 int /*<<< orphan*/  NVAPI_GPU_GETPERFPOLICIESINFO ; 
 int /*<<< orphan*/  NVAPI_GPU_GETPERFPOLICIESSTATUS ; 
 int /*<<< orphan*/  NVAPI_INITIALIZE ; 
 int /*<<< orphan*/  NVAPI_QUERYINTERFACE ; 
 int /*<<< orphan*/  NVAPI_UNLOAD ; 
 int /*<<< orphan*/  NvAPI_EnumPhysicalGPUs ; 
 int /*<<< orphan*/  NvAPI_GPU_GetBusId ; 
 int /*<<< orphan*/  NvAPI_GPU_GetBusSlotId ; 
 int /*<<< orphan*/  NvAPI_GPU_GetPerfPoliciesInfo ; 
 int /*<<< orphan*/  NvAPI_GPU_GetPerfPoliciesStatus ; 
 int /*<<< orphan*/  NvAPI_GetErrorMessage ; 
 int /*<<< orphan*/  NvAPI_Initialize ; 
 int /*<<< orphan*/  NvAPI_Unload ; 
 void* hc_dlopen (char*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvapi_QueryInterface ; 

__attribute__((used)) static int nvapi_init (hashcat_ctx_t *hashcat_ctx)
{
  hwmon_ctx_t *hwmon_ctx = hashcat_ctx->hwmon_ctx;

  NVAPI_PTR *nvapi = (NVAPI_PTR *) hwmon_ctx->hm_nvapi;

  memset (nvapi, 0, sizeof (NVAPI_PTR));

  #if defined (_WIN)

  #if defined (_WIN64)
  nvapi->lib = hc_dlopen ("nvapi64.dll");
  #else
  nvapi->lib = hc_dlopen ("nvapi.dll");
  #endif

  #else

  #if defined (__CYGWIN__)

  #if defined (__x86_x64__)
  nvapi->lib = hc_dlopen ("nvapi64.dll");
  #else
  nvapi->lib = hc_dlopen ("nvapi.dll");
  #endif

  #else
  nvapi->lib = hc_dlopen ("nvapi.so"); // uhm yes, but .. yeah
  #endif

  #endif

  if (!nvapi->lib)
  {
    //if (user_options->quiet == false)
    //  event_log_error (hashcat_ctx, "Load of NVAPI library failed. Proceeding without NVAPI HWMon enabled.");

    return -1;
  }

  HC_LOAD_FUNC(nvapi, nvapi_QueryInterface,             NVAPI_QUERYINTERFACE,             NVAPI,                0);
  HC_LOAD_ADDR(nvapi, NvAPI_Initialize,                 NVAPI_INITIALIZE,                 nvapi_QueryInterface, 0x0150E828U, NVAPI, 0);
  HC_LOAD_ADDR(nvapi, NvAPI_Unload,                     NVAPI_UNLOAD,                     nvapi_QueryInterface, 0xD22BDD7EU, NVAPI, 0);
  HC_LOAD_ADDR(nvapi, NvAPI_GetErrorMessage,            NVAPI_GETERRORMESSAGE,            nvapi_QueryInterface, 0x6C2D048CU, NVAPI, 0);
  HC_LOAD_ADDR(nvapi, NvAPI_EnumPhysicalGPUs,           NVAPI_ENUMPHYSICALGPUS,           nvapi_QueryInterface, 0xE5AC921FU, NVAPI, 0);
  HC_LOAD_ADDR(nvapi, NvAPI_GPU_GetPerfPoliciesInfo,    NVAPI_GPU_GETPERFPOLICIESINFO,    nvapi_QueryInterface, 0x409D9841U, NVAPI, 0);
  HC_LOAD_ADDR(nvapi, NvAPI_GPU_GetPerfPoliciesStatus,  NVAPI_GPU_GETPERFPOLICIESSTATUS,  nvapi_QueryInterface, 0x3D358A0CU, NVAPI, 0);
  HC_LOAD_ADDR(nvapi, NvAPI_GPU_GetBusId,               NVAPI_GPU_GETBUSID,               nvapi_QueryInterface, 0x1BE0B8E5U, NVAPI, 0);
  HC_LOAD_ADDR(nvapi, NvAPI_GPU_GetBusSlotId,           NVAPI_GPU_GETBUSSLOTID,           nvapi_QueryInterface, 0x2A0A350FU, NVAPI, 0);

  return 0;
}