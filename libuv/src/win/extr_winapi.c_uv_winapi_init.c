#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ sSetWinEventHook ;
typedef  int /*<<< orphan*/ * sRtlNtStatusToDosError ;
typedef  scalar_t__ sRtlGetVersion ;
typedef  scalar_t__ sRtlGenRandom ;
typedef  scalar_t__ sPowerRegisterSuspendResumeNotification ;
typedef  int /*<<< orphan*/ * sNtSetInformationFile ;
typedef  int /*<<< orphan*/ * sNtQueryVolumeInformationFile ;
typedef  int /*<<< orphan*/ * sNtQuerySystemInformation ;
typedef  int /*<<< orphan*/ * sNtQueryInformationProcess ;
typedef  int /*<<< orphan*/ * sNtQueryInformationFile ;
typedef  scalar_t__ sNtQueryDirectoryFile ;
typedef  int /*<<< orphan*/ * sNtDeviceIoControlFile ;
typedef  scalar_t__ sGetQueuedCompletionStatusEx ;
typedef  int /*<<< orphan*/ * HMODULE ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/ * GetModuleHandleA (char*) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * LoadLibraryA (char*) ; 
 scalar_t__ pGetQueuedCompletionStatusEx ; 
 int /*<<< orphan*/ * pNtDeviceIoControlFile ; 
 scalar_t__ pNtQueryDirectoryFile ; 
 int /*<<< orphan*/ * pNtQueryInformationFile ; 
 int /*<<< orphan*/ * pNtQueryInformationProcess ; 
 int /*<<< orphan*/ * pNtQuerySystemInformation ; 
 int /*<<< orphan*/ * pNtQueryVolumeInformationFile ; 
 int /*<<< orphan*/ * pNtSetInformationFile ; 
 scalar_t__ pPowerRegisterSuspendResumeNotification ; 
 scalar_t__ pRtlGenRandom ; 
 scalar_t__ pRtlGetVersion ; 
 int /*<<< orphan*/ * pRtlNtStatusToDosError ; 
 scalar_t__ pSetWinEventHook ; 
 int /*<<< orphan*/  uv_fatal_error (int /*<<< orphan*/ ,char*) ; 

void uv_winapi_init(void) {
  HMODULE ntdll_module;
  HMODULE powrprof_module;
  HMODULE user32_module;
  HMODULE kernel32_module;
  HMODULE advapi32_module;

  ntdll_module = GetModuleHandleA("ntdll.dll");
  if (ntdll_module == NULL) {
    uv_fatal_error(GetLastError(), "GetModuleHandleA");
  }

  pRtlGetVersion = (sRtlGetVersion) GetProcAddress(ntdll_module,
                                                   "RtlGetVersion");

  pRtlNtStatusToDosError = (sRtlNtStatusToDosError) GetProcAddress(
      ntdll_module,
      "RtlNtStatusToDosError");
  if (pRtlNtStatusToDosError == NULL) {
    uv_fatal_error(GetLastError(), "GetProcAddress");
  }

  pNtDeviceIoControlFile = (sNtDeviceIoControlFile) GetProcAddress(
      ntdll_module,
      "NtDeviceIoControlFile");
  if (pNtDeviceIoControlFile == NULL) {
    uv_fatal_error(GetLastError(), "GetProcAddress");
  }

  pNtQueryInformationFile = (sNtQueryInformationFile) GetProcAddress(
      ntdll_module,
      "NtQueryInformationFile");
  if (pNtQueryInformationFile == NULL) {
    uv_fatal_error(GetLastError(), "GetProcAddress");
  }

  pNtSetInformationFile = (sNtSetInformationFile) GetProcAddress(
      ntdll_module,
      "NtSetInformationFile");
  if (pNtSetInformationFile == NULL) {
    uv_fatal_error(GetLastError(), "GetProcAddress");
  }

  pNtQueryVolumeInformationFile = (sNtQueryVolumeInformationFile)
      GetProcAddress(ntdll_module, "NtQueryVolumeInformationFile");
  if (pNtQueryVolumeInformationFile == NULL) {
    uv_fatal_error(GetLastError(), "GetProcAddress");
  }

  pNtQueryDirectoryFile = (sNtQueryDirectoryFile)
      GetProcAddress(ntdll_module, "NtQueryDirectoryFile");
  if (pNtQueryVolumeInformationFile == NULL) {
    uv_fatal_error(GetLastError(), "GetProcAddress");
  }

  pNtQuerySystemInformation = (sNtQuerySystemInformation) GetProcAddress(
      ntdll_module,
      "NtQuerySystemInformation");
  if (pNtQuerySystemInformation == NULL) {
    uv_fatal_error(GetLastError(), "GetProcAddress");
  }

  pNtQueryInformationProcess = (sNtQueryInformationProcess) GetProcAddress(
      ntdll_module,
      "NtQueryInformationProcess");
  if (pNtQueryInformationProcess == NULL) {
    uv_fatal_error(GetLastError(), "GetProcAddress");
  }

  kernel32_module = GetModuleHandleA("kernel32.dll");
  if (kernel32_module == NULL) {
    uv_fatal_error(GetLastError(), "GetModuleHandleA");
  }

  pGetQueuedCompletionStatusEx = (sGetQueuedCompletionStatusEx) GetProcAddress(
      kernel32_module,
      "GetQueuedCompletionStatusEx");

  powrprof_module = LoadLibraryA("powrprof.dll");
  if (powrprof_module != NULL) {
    pPowerRegisterSuspendResumeNotification = (sPowerRegisterSuspendResumeNotification)
      GetProcAddress(powrprof_module, "PowerRegisterSuspendResumeNotification");
  }

  user32_module = LoadLibraryA("user32.dll");
  if (user32_module != NULL) {
    pSetWinEventHook = (sSetWinEventHook)
      GetProcAddress(user32_module, "SetWinEventHook");
  }

  advapi32_module = GetModuleHandleA("advapi32.dll");
  if (advapi32_module == NULL) {
    uv_fatal_error(GetLastError(), "GetModuleHandleA");
  }

  pRtlGenRandom =
      (sRtlGenRandom) GetProcAddress(advapi32_module, "SystemFunction036");
}