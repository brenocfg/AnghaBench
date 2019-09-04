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
struct TYPE_8__ {char* version; int* sysname; char* release; int* machine; } ;
typedef  TYPE_1__ uv_utsname_t ;
typedef  int /*<<< orphan*/  product_name_w ;
typedef  int /*<<< orphan*/  os_info ;
typedef  int WCHAR ;
struct TYPE_10__ {int dwOSVersionInfoSize; int* szCSDVersion; scalar_t__ dwBuildNumber; scalar_t__ dwMinorVersion; scalar_t__ dwMajorVersion; } ;
struct TYPE_9__ {int wProcessorArchitecture; int wProcessorLevel; } ;
typedef  TYPE_2__ SYSTEM_INFO ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_3__ OSVERSIONINFOW ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetSystemInfo (TYPE_2__*) ; 
 scalar_t__ GetVersionExW (TYPE_3__*) ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_QUERY_VALUE ; 
#define  PROCESSOR_ARCHITECTURE_ALPHA 137 
#define  PROCESSOR_ARCHITECTURE_ALPHA64 136 
#define  PROCESSOR_ARCHITECTURE_AMD64 135 
#define  PROCESSOR_ARCHITECTURE_ARM 134 
#define  PROCESSOR_ARCHITECTURE_IA32_ON_WIN64 133 
#define  PROCESSOR_ARCHITECTURE_IA64 132 
#define  PROCESSOR_ARCHITECTURE_INTEL 131 
#define  PROCESSOR_ARCHITECTURE_MIPS 130 
#define  PROCESSOR_ARCHITECTURE_PPC 129 
#define  PROCESSOR_ARCHITECTURE_SHX 128 
 int /*<<< orphan*/  RRF_RT_REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int RegGetValueW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int RegOpenKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int UV_EINVAL ; 
 int WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pRtlGetVersion (TYPE_3__*) ; 
 int snprintf (char*,int,char*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  uv__once_init () ; 
 int /*<<< orphan*/  uv__strscpy (int*,char*,int) ; 
 int uv_translate_sys_error (int /*<<< orphan*/ ) ; 

int uv_os_uname(uv_utsname_t* buffer) {
  /* Implementation loosely based on
     https://github.com/gagern/gnulib/blob/master/lib/uname.c */
  OSVERSIONINFOW os_info;
  SYSTEM_INFO system_info;
  HKEY registry_key;
  WCHAR product_name_w[256];
  DWORD product_name_w_size;
  int version_size;
  int processor_level;
  int r;

  if (buffer == NULL)
    return UV_EINVAL;

  uv__once_init();
  os_info.dwOSVersionInfoSize = sizeof(os_info);
  os_info.szCSDVersion[0] = L'\0';

  /* Try calling RtlGetVersion(), and fall back to the deprecated GetVersionEx()
     if RtlGetVersion() is not available. */
  if (pRtlGetVersion) {
    pRtlGetVersion(&os_info);
  } else {
    /* Silence GetVersionEx() deprecation warning. */
    #pragma warning(suppress : 4996)
    if (GetVersionExW(&os_info) == 0) {
      r = uv_translate_sys_error(GetLastError());
      goto error;
    }
  }

  /* Populate the version field. */
  version_size = 0;
  r = RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                    L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion",
                    0,
                    KEY_QUERY_VALUE,
                    &registry_key);

  if (r == ERROR_SUCCESS) {
    product_name_w_size = sizeof(product_name_w);
    r = RegGetValueW(registry_key,
                     NULL,
                     L"ProductName",
                     RRF_RT_REG_SZ,
                     NULL,
                     (PVOID) product_name_w,
                     &product_name_w_size);
    RegCloseKey(registry_key);

    if (r == ERROR_SUCCESS) {
      version_size = WideCharToMultiByte(CP_UTF8,
                                         0,
                                         product_name_w,
                                         -1,
                                         buffer->version,
                                         sizeof(buffer->version),
                                         NULL,
                                         NULL);
      if (version_size == 0) {
        r = uv_translate_sys_error(GetLastError());
        goto error;
      }
    }
  }

  /* Append service pack information to the version if present. */
  if (os_info.szCSDVersion[0] != L'\0') {
    if (version_size > 0)
      buffer->version[version_size - 1] = ' ';

    if (WideCharToMultiByte(CP_UTF8,
                            0,
                            os_info.szCSDVersion,
                            -1,
                            buffer->version + version_size,
                            sizeof(buffer->version) - version_size,
                            NULL,
                            NULL) == 0) {
      r = uv_translate_sys_error(GetLastError());
      goto error;
    }
  }

  /* Populate the sysname field. */
#ifdef __MINGW32__
  r = snprintf(buffer->sysname,
               sizeof(buffer->sysname),
               "MINGW32_NT-%u.%u",
               (unsigned int) os_info.dwMajorVersion,
               (unsigned int) os_info.dwMinorVersion);
  assert(r < sizeof(buffer->sysname));
#else
  uv__strscpy(buffer->sysname, "Windows_NT", sizeof(buffer->sysname));
#endif

  /* Populate the release field. */
  r = snprintf(buffer->release,
               sizeof(buffer->release),
               "%d.%d.%d",
               (unsigned int) os_info.dwMajorVersion,
               (unsigned int) os_info.dwMinorVersion,
               (unsigned int) os_info.dwBuildNumber);
  assert(r < sizeof(buffer->release));

  /* Populate the machine field. */
  GetSystemInfo(&system_info);

  switch (system_info.wProcessorArchitecture) {
    case PROCESSOR_ARCHITECTURE_AMD64:
      uv__strscpy(buffer->machine, "x86_64", sizeof(buffer->machine));
      break;
    case PROCESSOR_ARCHITECTURE_IA64:
      uv__strscpy(buffer->machine, "ia64", sizeof(buffer->machine));
      break;
    case PROCESSOR_ARCHITECTURE_INTEL:
      uv__strscpy(buffer->machine, "i386", sizeof(buffer->machine));

      if (system_info.wProcessorLevel > 3) {
        processor_level = system_info.wProcessorLevel < 6 ?
                          system_info.wProcessorLevel : 6;
        buffer->machine[1] = '0' + processor_level;
      }

      break;
    case PROCESSOR_ARCHITECTURE_IA32_ON_WIN64:
      uv__strscpy(buffer->machine, "i686", sizeof(buffer->machine));
      break;
    case PROCESSOR_ARCHITECTURE_MIPS:
      uv__strscpy(buffer->machine, "mips", sizeof(buffer->machine));
      break;
    case PROCESSOR_ARCHITECTURE_ALPHA:
    case PROCESSOR_ARCHITECTURE_ALPHA64:
      uv__strscpy(buffer->machine, "alpha", sizeof(buffer->machine));
      break;
    case PROCESSOR_ARCHITECTURE_PPC:
      uv__strscpy(buffer->machine, "powerpc", sizeof(buffer->machine));
      break;
    case PROCESSOR_ARCHITECTURE_SHX:
      uv__strscpy(buffer->machine, "sh", sizeof(buffer->machine));
      break;
    case PROCESSOR_ARCHITECTURE_ARM:
      uv__strscpy(buffer->machine, "arm", sizeof(buffer->machine));
      break;
    default:
      uv__strscpy(buffer->machine, "unknown", sizeof(buffer->machine));
      break;
  }

  return 0;

error:
  buffer->sysname[0] = '\0';
  buffer->release[0] = '\0';
  buffer->version[0] = '\0';
  buffer->machine[0] = '\0';
  return r;
}