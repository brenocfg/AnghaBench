#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int user; int sys; int idle; int irq; scalar_t__ nice; } ;
struct TYPE_19__ {int QuadPart; } ;
struct TYPE_18__ {int QuadPart; } ;
struct TYPE_17__ {int QuadPart; } ;
struct TYPE_16__ {int QuadPart; } ;
struct TYPE_21__ {int speed; struct TYPE_21__* model; TYPE_5__ cpu_times; TYPE_4__ InterruptTime; TYPE_3__ IdleTime; TYPE_2__ KernelTime; TYPE_1__ UserTime; } ;
typedef  TYPE_6__ uv_cpu_info_t ;
typedef  int /*<<< orphan*/  cpu_speed ;
typedef  int /*<<< orphan*/  cpu_brand ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int ULONG ;
struct TYPE_22__ {int dwNumberOfProcessors; } ;
typedef  TYPE_6__ SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION ;
typedef  TYPE_8__ SYSTEM_INFO ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int ERROR_OUTOFMEMORY ; 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetSystemInfo (TYPE_8__*) ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_QUERY_VALUE ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int RegOpenKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int RegQueryValueExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  SystemProcessorPerformanceInformation ; 
 size_t _snwprintf (int /*<<< orphan*/ *,size_t,char*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pNtQuerySystemInformation (int /*<<< orphan*/ ,TYPE_6__*,int,int*) ; 
 int pRtlNtStatusToDosError (int /*<<< orphan*/ ) ; 
 TYPE_6__* uv__calloc (int,int) ; 
 int /*<<< orphan*/  uv__convert_utf16_to_utf8 (int /*<<< orphan*/ *,int,TYPE_6__**) ; 
 int /*<<< orphan*/  uv__free (TYPE_6__*) ; 
 TYPE_6__* uv__malloc (int) ; 
 int /*<<< orphan*/  uv__once_init () ; 
 int uv_translate_sys_error (int) ; 

int uv_cpu_info(uv_cpu_info_t** cpu_infos_ptr, int* cpu_count_ptr) {
  uv_cpu_info_t* cpu_infos;
  SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION* sppi;
  DWORD sppi_size;
  SYSTEM_INFO system_info;
  DWORD cpu_count, i;
  NTSTATUS status;
  ULONG result_size;
  int err;
  uv_cpu_info_t* cpu_info;

  cpu_infos = NULL;
  cpu_count = 0;
  sppi = NULL;

  uv__once_init();

  GetSystemInfo(&system_info);
  cpu_count = system_info.dwNumberOfProcessors;

  cpu_infos = uv__calloc(cpu_count, sizeof *cpu_infos);
  if (cpu_infos == NULL) {
    err = ERROR_OUTOFMEMORY;
    goto error;
  }

  sppi_size = cpu_count * sizeof(*sppi);
  sppi = uv__malloc(sppi_size);
  if (sppi == NULL) {
    err = ERROR_OUTOFMEMORY;
    goto error;
  }

  status = pNtQuerySystemInformation(SystemProcessorPerformanceInformation,
                                     sppi,
                                     sppi_size,
                                     &result_size);
  if (!NT_SUCCESS(status)) {
    err = pRtlNtStatusToDosError(status);
    goto error;
  }

  assert(result_size == sppi_size);

  for (i = 0; i < cpu_count; i++) {
    WCHAR key_name[128];
    HKEY processor_key;
    DWORD cpu_speed;
    DWORD cpu_speed_size = sizeof(cpu_speed);
    WCHAR cpu_brand[256];
    DWORD cpu_brand_size = sizeof(cpu_brand);
    size_t len;

    len = _snwprintf(key_name,
                     ARRAY_SIZE(key_name),
                     L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\%d",
                     i);

    assert(len > 0 && len < ARRAY_SIZE(key_name));

    err = RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                        key_name,
                        0,
                        KEY_QUERY_VALUE,
                        &processor_key);
    if (err != ERROR_SUCCESS) {
      goto error;
    }

    err = RegQueryValueExW(processor_key,
                           L"~MHz",
                           NULL,
                           NULL,
                           (BYTE*)&cpu_speed,
                           &cpu_speed_size);
    if (err != ERROR_SUCCESS) {
      RegCloseKey(processor_key);
      goto error;
    }

    err = RegQueryValueExW(processor_key,
                           L"ProcessorNameString",
                           NULL,
                           NULL,
                           (BYTE*)&cpu_brand,
                           &cpu_brand_size);
    RegCloseKey(processor_key);
    if (err != ERROR_SUCCESS)
      goto error;

    cpu_info = &cpu_infos[i];
    cpu_info->speed = cpu_speed;
    cpu_info->cpu_times.user = sppi[i].UserTime.QuadPart / 10000;
    cpu_info->cpu_times.sys = (sppi[i].KernelTime.QuadPart -
        sppi[i].IdleTime.QuadPart) / 10000;
    cpu_info->cpu_times.idle = sppi[i].IdleTime.QuadPart / 10000;
    cpu_info->cpu_times.irq = sppi[i].InterruptTime.QuadPart / 10000;
    cpu_info->cpu_times.nice = 0;

    uv__convert_utf16_to_utf8(cpu_brand,
                              cpu_brand_size / sizeof(WCHAR),
                              &(cpu_info->model));
  }

  uv__free(sppi);

  *cpu_count_ptr = cpu_count;
  *cpu_infos_ptr = cpu_infos;

  return 0;

 error:
  if (cpu_infos != NULL) {
    /* This is safe because the cpu_infos array is zeroed on allocation. */
    for (i = 0; i < cpu_count; i++)
      uv__free(cpu_infos[i].model);
  }

  uv__free(cpu_infos);
  uv__free(sppi);

  return uv_translate_sys_error(err);
}