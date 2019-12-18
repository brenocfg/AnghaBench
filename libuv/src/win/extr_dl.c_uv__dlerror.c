#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_4__ {char* errmsg; } ;
typedef  TYPE_1__ uv_lib_t ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  scalar_t__ DWORD_PTR ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_BAD_EXE_FORMAT ; 
 scalar_t__ ERROR_MUI_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_RESOURCE_TYPE_NOT_FOUND ; 
 int FORMAT_MESSAGE_ALLOCATE_BUFFER ; 
 int FORMAT_MESSAGE_ARGUMENT_ARRAY ; 
 int FORMAT_MESSAGE_FROM_STRING ; 
 int FORMAT_MESSAGE_FROM_SYSTEM ; 
 int FORMAT_MESSAGE_IGNORE_INSERTS ; 
 scalar_t__ FormatMessageA (int,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  LANG_ENGLISH ; 
 int /*<<< orphan*/  LocalFree (char*) ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUBLANG_ENGLISH_US ; 
 scalar_t__ strstr (char*,char*) ; 
 int /*<<< orphan*/  uv__format_fallback_error (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static int uv__dlerror(uv_lib_t* lib, const char* filename, DWORD errorno) {
  DWORD_PTR arg;
  DWORD res;
  char* msg;

  if (lib->errmsg) {
    LocalFree(lib->errmsg);
    lib->errmsg = NULL;
  }

  if (errorno == 0)
    return 0;

  res = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                       FORMAT_MESSAGE_FROM_SYSTEM |
                       FORMAT_MESSAGE_IGNORE_INSERTS, NULL, errorno,
                       MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
                       (LPSTR) &lib->errmsg, 0, NULL);

  if (!res && (GetLastError() == ERROR_MUI_FILE_NOT_FOUND ||
               GetLastError() == ERROR_RESOURCE_TYPE_NOT_FOUND)) {
    res = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                         FORMAT_MESSAGE_FROM_SYSTEM |
                         FORMAT_MESSAGE_IGNORE_INSERTS, NULL, errorno,
                         0, (LPSTR) &lib->errmsg, 0, NULL);
  }

  if (res && errorno == ERROR_BAD_EXE_FORMAT && strstr(lib->errmsg, "%1")) {
    msg = lib->errmsg;
    lib->errmsg = NULL;
    arg = (DWORD_PTR) filename;
    res = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                         FORMAT_MESSAGE_ARGUMENT_ARRAY |
                         FORMAT_MESSAGE_FROM_STRING,
                         msg,
                         0, 0, (LPSTR) &lib->errmsg, 0, (va_list*) &arg);
    LocalFree(msg);
  }

  if (!res)
    uv__format_fallback_error(lib, errorno);

  return -1;
}