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
struct TYPE_7__ {scalar_t__ hm_adl; } ;
typedef  TYPE_1__ hwmon_ctx_t ;
struct TYPE_8__ {TYPE_1__* hwmon_ctx; } ;
typedef  TYPE_2__ hashcat_ctx_t ;
struct TYPE_9__ {void* lib; } ;
typedef  TYPE_3__ ADL_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  ADL ; 
 int /*<<< orphan*/  ADL_ADAPTER_ACTIVE_GET ; 
 int /*<<< orphan*/  ADL_ADAPTER_ADAPTERINFO_GET ; 
 int /*<<< orphan*/  ADL_ADAPTER_ID_GET ; 
 int /*<<< orphan*/  ADL_ADAPTER_NUMBEROFADAPTERS_GET ; 
 int /*<<< orphan*/  ADL_ADAPTER_VIDEOBIOSINFO_GET ; 
 int /*<<< orphan*/  ADL_Adapter_Active_Get ; 
 int /*<<< orphan*/  ADL_Adapter_AdapterInfo_Get ; 
 int /*<<< orphan*/  ADL_Adapter_ID_Get ; 
 int /*<<< orphan*/  ADL_Adapter_NumberOfAdapters_Get ; 
 int /*<<< orphan*/  ADL_Adapter_VideoBiosInfo_Get ; 
 int /*<<< orphan*/  ADL_DISPLAY_DISPLAYINFO_GET ; 
 int /*<<< orphan*/  ADL_Display_DisplayInfo_Get ; 
 int /*<<< orphan*/  ADL_MAIN_CONTROL_CREATE ; 
 int /*<<< orphan*/  ADL_MAIN_CONTROL_DESTROY ; 
 int /*<<< orphan*/  ADL_Main_Control_Create ; 
 int /*<<< orphan*/  ADL_Main_Control_Destroy ; 
 int /*<<< orphan*/  ADL_OVERDRIVE5_CURRENTACTIVITY_GET ; 
 int /*<<< orphan*/  ADL_OVERDRIVE5_FANSPEEDINFO_GET ; 
 int /*<<< orphan*/  ADL_OVERDRIVE5_FANSPEED_GET ; 
 int /*<<< orphan*/  ADL_OVERDRIVE5_TEMPERATURE_GET ; 
 int /*<<< orphan*/  ADL_OVERDRIVE5_THERMALDEVICES_ENUM ; 
 int /*<<< orphan*/  ADL_OVERDRIVE6_CAPABILITIES_GET ; 
 int /*<<< orphan*/  ADL_OVERDRIVE6_CURRENTSTATUS_GET ; 
 int /*<<< orphan*/  ADL_OVERDRIVE6_FANSPEED_GET ; 
 int /*<<< orphan*/  ADL_OVERDRIVE6_STATEINFO_GET ; 
 int /*<<< orphan*/  ADL_OVERDRIVE6_TARGETTEMPERATUREDATA_GET ; 
 int /*<<< orphan*/  ADL_OVERDRIVE6_TARGETTEMPERATURERANGEINFO_GET ; 
 int /*<<< orphan*/  ADL_OVERDRIVE6_TEMPERATURE_GET ; 
 int /*<<< orphan*/  ADL_OVERDRIVE_CAPS ; 
 int /*<<< orphan*/  ADL_Overdrive5_CurrentActivity_Get ; 
 int /*<<< orphan*/  ADL_Overdrive5_FanSpeedInfo_Get ; 
 int /*<<< orphan*/  ADL_Overdrive5_FanSpeed_Get ; 
 int /*<<< orphan*/  ADL_Overdrive5_Temperature_Get ; 
 int /*<<< orphan*/  ADL_Overdrive5_ThermalDevices_Enum ; 
 int /*<<< orphan*/  ADL_Overdrive6_Capabilities_Get ; 
 int /*<<< orphan*/  ADL_Overdrive6_CurrentStatus_Get ; 
 int /*<<< orphan*/  ADL_Overdrive6_FanSpeed_Get ; 
 int /*<<< orphan*/  ADL_Overdrive6_StateInfo_Get ; 
 int /*<<< orphan*/  ADL_Overdrive6_TargetTemperatureData_Get ; 
 int /*<<< orphan*/  ADL_Overdrive6_TargetTemperatureRangeInfo_Get ; 
 int /*<<< orphan*/  ADL_Overdrive6_Temperature_Get ; 
 int /*<<< orphan*/  ADL_Overdrive_Caps ; 
 int /*<<< orphan*/  HC_LOAD_FUNC (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* hc_dlopen (char*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int adl_init (hashcat_ctx_t *hashcat_ctx)
{
  hwmon_ctx_t *hwmon_ctx = hashcat_ctx->hwmon_ctx;

  ADL_PTR *adl = (ADL_PTR *) hwmon_ctx->hm_adl;

  memset (adl, 0, sizeof (ADL_PTR));

  #if defined (_WIN)
  adl->lib = hc_dlopen ("atiadlxx.dll");

  if (!adl->lib)
  {
    adl->lib = hc_dlopen ("atiadlxy.dll");
  }
  #elif defined (__CYGWIN__)
  adl->lib = hc_dlopen ("atiadlxx.dll");

  if (!adl->lib)
  {
    adl->lib = hc_dlopen ("atiadlxy.dll");
  }
  #elif defined (_POSIX)
  adl->lib = hc_dlopen ("libatiadlxx.so");
  #endif

  if (!adl->lib)
  {
    //if (user_options->quiet == false)
    //  event_log_error (hashcat_ctx, "Load of ADL library failed. Proceeding without ADL HWMon enabled.");

    return -1;
  }

  HC_LOAD_FUNC(adl, ADL_Main_Control_Destroy, ADL_MAIN_CONTROL_DESTROY, ADL, 0);
  HC_LOAD_FUNC(adl, ADL_Main_Control_Create, ADL_MAIN_CONTROL_CREATE, ADL, 0);
  HC_LOAD_FUNC(adl, ADL_Adapter_NumberOfAdapters_Get, ADL_ADAPTER_NUMBEROFADAPTERS_GET, ADL, 0);
  HC_LOAD_FUNC(adl, ADL_Adapter_AdapterInfo_Get, ADL_ADAPTER_ADAPTERINFO_GET, ADL, 0);
  HC_LOAD_FUNC(adl, ADL_Display_DisplayInfo_Get, ADL_DISPLAY_DISPLAYINFO_GET, ADL, 0);
  HC_LOAD_FUNC(adl, ADL_Adapter_ID_Get, ADL_ADAPTER_ID_GET, ADL, 0);
  HC_LOAD_FUNC(adl, ADL_Adapter_VideoBiosInfo_Get, ADL_ADAPTER_VIDEOBIOSINFO_GET, ADL, 0);
  HC_LOAD_FUNC(adl, ADL_Overdrive5_ThermalDevices_Enum, ADL_OVERDRIVE5_THERMALDEVICES_ENUM, ADL, 0);
  HC_LOAD_FUNC(adl, ADL_Overdrive5_Temperature_Get, ADL_OVERDRIVE5_TEMPERATURE_GET, ADL, 0);
  HC_LOAD_FUNC(adl, ADL_Overdrive6_Temperature_Get, ADL_OVERDRIVE6_TEMPERATURE_GET, ADL, 0);
  HC_LOAD_FUNC(adl, ADL_Overdrive5_CurrentActivity_Get, ADL_OVERDRIVE5_CURRENTACTIVITY_GET, ADL, 0);
  HC_LOAD_FUNC(adl, ADL_Overdrive5_FanSpeedInfo_Get, ADL_OVERDRIVE5_FANSPEEDINFO_GET, ADL, 0);
  HC_LOAD_FUNC(adl, ADL_Overdrive5_FanSpeed_Get, ADL_OVERDRIVE5_FANSPEED_GET, ADL, 0);
  HC_LOAD_FUNC(adl, ADL_Overdrive6_FanSpeed_Get, ADL_OVERDRIVE6_FANSPEED_GET, ADL, 0);
  HC_LOAD_FUNC(adl, ADL_Adapter_Active_Get, ADL_ADAPTER_ACTIVE_GET, ADL, 0);
  HC_LOAD_FUNC(adl, ADL_Overdrive_Caps, ADL_OVERDRIVE_CAPS, ADL, 0);
  HC_LOAD_FUNC(adl, ADL_Overdrive6_Capabilities_Get, ADL_OVERDRIVE6_CAPABILITIES_GET, ADL, 0);
  HC_LOAD_FUNC(adl, ADL_Overdrive6_StateInfo_Get, ADL_OVERDRIVE6_STATEINFO_GET, ADL, 0);
  HC_LOAD_FUNC(adl, ADL_Overdrive6_CurrentStatus_Get, ADL_OVERDRIVE6_CURRENTSTATUS_GET, ADL, 0);
  HC_LOAD_FUNC(adl, ADL_Overdrive6_TargetTemperatureData_Get, ADL_OVERDRIVE6_TARGETTEMPERATUREDATA_GET, ADL, 0);
  HC_LOAD_FUNC(adl, ADL_Overdrive6_TargetTemperatureRangeInfo_Get, ADL_OVERDRIVE6_TARGETTEMPERATURERANGEINFO_GET, ADL, 0);

  return 0;
}