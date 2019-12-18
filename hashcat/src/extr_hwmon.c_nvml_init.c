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
typedef  int ssize_t ;
struct TYPE_7__ {scalar_t__ hm_nvml; } ;
typedef  TYPE_1__ hwmon_ctx_t ;
struct TYPE_8__ {TYPE_1__* hwmon_ctx; } ;
typedef  TYPE_2__ hashcat_ctx_t ;
struct TYPE_9__ {void* lib; } ;
typedef  TYPE_3__ NVML_PTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  HCFILE ;
typedef  int DWORD ;

/* Variables and functions */
 int CCP_PROC_CYGDRIVE ; 
 int CCP_WIN_A_TO_POSIX ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HC_LOAD_FUNC (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_QUERY_VALUE ; 
 int /*<<< orphan*/  NVML ; 
 int /*<<< orphan*/  NVML_DEVICE_GET_CLOCKINFO ; 
 int /*<<< orphan*/  NVML_DEVICE_GET_COUNT ; 
 int /*<<< orphan*/  NVML_DEVICE_GET_CURRENTCLOCKSTHROTTLEREASONS ; 
 int /*<<< orphan*/  NVML_DEVICE_GET_CURRPCIELINKGENERATION ; 
 int /*<<< orphan*/  NVML_DEVICE_GET_CURRPCIELINKWIDTH ; 
 int /*<<< orphan*/  NVML_DEVICE_GET_FAN_SPEED ; 
 int /*<<< orphan*/  NVML_DEVICE_GET_HANDLE_BY_INDEX ; 
 int /*<<< orphan*/  NVML_DEVICE_GET_NAME ; 
 int /*<<< orphan*/  NVML_DEVICE_GET_PCIINFO ; 
 int /*<<< orphan*/  NVML_DEVICE_GET_SUPPORTEDCLOCKSTHROTTLEREASONS ; 
 int /*<<< orphan*/  NVML_DEVICE_GET_TEMPERATURE ; 
 int /*<<< orphan*/  NVML_DEVICE_GET_THRESHOLD ; 
 int /*<<< orphan*/  NVML_DEVICE_GET_UTILIZATION_RATES ; 
 int /*<<< orphan*/  NVML_ERROR_STRING ; 
 int /*<<< orphan*/  NVML_INIT ; 
 int /*<<< orphan*/  NVML_SHUTDOWN ; 
 int REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int*) ; 
 int cygwin_conv_path (int,char*,char*,int) ; 
 void* hc_dlopen (char*) ; 
 int /*<<< orphan*/  hc_fclose (int /*<<< orphan*/ *) ; 
 int hc_fopen (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  hc_fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hcfree (char*) ; 
 scalar_t__ hcmalloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvmlDeviceGetClockInfo ; 
 int /*<<< orphan*/  nvmlDeviceGetCount ; 
 int /*<<< orphan*/  nvmlDeviceGetCurrPcieLinkGeneration ; 
 int /*<<< orphan*/  nvmlDeviceGetCurrPcieLinkWidth ; 
 int /*<<< orphan*/  nvmlDeviceGetCurrentClocksThrottleReasons ; 
 int /*<<< orphan*/  nvmlDeviceGetFanSpeed ; 
 int /*<<< orphan*/  nvmlDeviceGetHandleByIndex ; 
 int /*<<< orphan*/  nvmlDeviceGetName ; 
 int /*<<< orphan*/  nvmlDeviceGetPciInfo ; 
 int /*<<< orphan*/  nvmlDeviceGetSupportedClocksThrottleReasons ; 
 int /*<<< orphan*/  nvmlDeviceGetTemperature ; 
 int /*<<< orphan*/  nvmlDeviceGetTemperatureThreshold ; 
 int /*<<< orphan*/  nvmlDeviceGetUtilizationRates ; 
 int /*<<< orphan*/  nvmlErrorString ; 
 int /*<<< orphan*/  nvmlInit ; 
 int /*<<< orphan*/  nvmlShutdown ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

__attribute__((used)) static int nvml_init (hashcat_ctx_t *hashcat_ctx)
{
  hwmon_ctx_t *hwmon_ctx = hashcat_ctx->hwmon_ctx;

  NVML_PTR *nvml = (NVML_PTR *) hwmon_ctx->hm_nvml;

  memset (nvml, 0, sizeof (NVML_PTR));

  #if defined (_WIN)

  nvml->lib = hc_dlopen ("nvml.dll");

  if (!nvml->lib)
  {
    DWORD BufferSize = 1024;

    DWORD Type = REG_SZ;

    char *Buffer = (char *) hcmalloc (BufferSize + 1);

    HKEY hKey = 0;

    if (RegOpenKeyExA (HKEY_LOCAL_MACHINE, "SOFTWARE\\NVIDIA Corporation\\Global\\NVSMI", 0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS)
    {
      if (RegQueryValueExA (hKey, "NVSMIPATH", NULL, &Type, (LPBYTE)Buffer, &BufferSize) == ERROR_SUCCESS)
      {
        Buffer[BufferSize] = 0;
      }
      else
      {
        //if (user_options->quiet == false)
        //  event_log_error (hashcat_ctx, "NVML library load failed. Proceeding without NVML HWMon enabled.");

        return -1;
      }

      RegCloseKey (hKey);
    }
    else
    {
      //if (user_options->quiet == false)
      //  event_log_error (hashcat_ctx, "NVML library load failed. Proceeding without NVML HWMon enabled.");

      return -1;
    }

    strcat (Buffer, "\\nvml.dll");

    nvml->lib = hc_dlopen (Buffer);

    hcfree (Buffer);
  }

  #elif defined (__CYGWIN__)

  nvml->lib = hc_dlopen("nvml.dll");

  if (!nvml->lib)
  {
    HCFILE nvml_lib;

    if (hc_fopen (&nvml_lib, "/proc/registry/HKEY_LOCAL_MACHINE/SOFTWARE/NVIDIA Corporation/Global/NVSMI/NVSMIPATH", "rb") == false)
    {
      //if (user_options->quiet == false)
      //  event_log_error (hashcat_ctx, "NVML library load failed: %m. Proceeding without NVML HWMon enabled.");

      return -1;
    }

    char *nvml_winpath, *nvml_cygpath;

    nvml_winpath = (char *) hcmalloc (100);

    hc_fread (nvml_winpath, 100, 1, &nvml_lib);

    hc_fclose (&nvml_lib);

    ssize_t size = cygwin_conv_path (CCP_WIN_A_TO_POSIX | CCP_PROC_CYGDRIVE, nvml_winpath, NULL, 0);

    if (size > 0)
    {
      nvml_cygpath = (char *) hcmalloc (size + 9);

      cygwin_conv_path (CCP_WIN_A_TO_POSIX | CCP_PROC_CYGDRIVE, nvml_winpath, nvml_cygpath, size);
    }
    else
    {
      //if (user_options->quiet == false)
      //  event_log_error (hashcat_ctx, "Could not find NVML on this system. Proceeding without NVML HWMon enabled.");

      return -1;
    }

    strcat (nvml_cygpath, "/nvml.dll");

    nvml->lib = hc_dlopen (nvml_cygpath);
  }

  #elif defined (_POSIX)

  nvml->lib = hc_dlopen ("libnvidia-ml.so");

  if (!nvml->lib)
  {
    nvml->lib = hc_dlopen ("libnvidia-ml.so.1");
  }

  #endif

  if (!nvml->lib)
  {
    //if (user_options->quiet == false)
    //  event_log_error (hashcat_ctx, "NVML library load failed. Proceeding without NVML HWMon enabled.");

    return -1;
  }

  HC_LOAD_FUNC(nvml, nvmlErrorString, NVML_ERROR_STRING, NVML, 0);
  HC_LOAD_FUNC(nvml, nvmlInit, NVML_INIT, NVML, 0);
  HC_LOAD_FUNC(nvml, nvmlShutdown, NVML_SHUTDOWN, NVML, 0);
  HC_LOAD_FUNC(nvml, nvmlDeviceGetCount, NVML_DEVICE_GET_COUNT, NVML, 0);
  HC_LOAD_FUNC(nvml, nvmlDeviceGetName, NVML_DEVICE_GET_NAME, NVML, 0);
  HC_LOAD_FUNC(nvml, nvmlDeviceGetHandleByIndex, NVML_DEVICE_GET_HANDLE_BY_INDEX, NVML, 0);
  HC_LOAD_FUNC(nvml, nvmlDeviceGetTemperature, NVML_DEVICE_GET_TEMPERATURE, NVML, 0);
  HC_LOAD_FUNC(nvml, nvmlDeviceGetFanSpeed, NVML_DEVICE_GET_FAN_SPEED, NVML, 0);
  HC_LOAD_FUNC(nvml, nvmlDeviceGetUtilizationRates, NVML_DEVICE_GET_UTILIZATION_RATES, NVML, 0);
  HC_LOAD_FUNC(nvml, nvmlDeviceGetClockInfo, NVML_DEVICE_GET_CLOCKINFO, NVML, 0);
  HC_LOAD_FUNC(nvml, nvmlDeviceGetTemperatureThreshold, NVML_DEVICE_GET_THRESHOLD, NVML, 0);
  HC_LOAD_FUNC(nvml, nvmlDeviceGetCurrPcieLinkGeneration, NVML_DEVICE_GET_CURRPCIELINKGENERATION, NVML, 0);
  HC_LOAD_FUNC(nvml, nvmlDeviceGetCurrPcieLinkWidth, NVML_DEVICE_GET_CURRPCIELINKWIDTH, NVML, 0);
  HC_LOAD_FUNC(nvml, nvmlDeviceGetCurrentClocksThrottleReasons, NVML_DEVICE_GET_CURRENTCLOCKSTHROTTLEREASONS, NVML, 0);
  HC_LOAD_FUNC(nvml, nvmlDeviceGetSupportedClocksThrottleReasons, NVML_DEVICE_GET_SUPPORTEDCLOCKSTHROTTLEREASONS, NVML, 0);
  HC_LOAD_FUNC(nvml, nvmlDeviceGetPciInfo, NVML_DEVICE_GET_PCIINFO, NVML, 0);

  return 0;
}