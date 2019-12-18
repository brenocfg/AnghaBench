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
typedef  int /*<<< orphan*/  si ;
struct TYPE_7__ {char* name; int /*<<< orphan*/  process; scalar_t__ stdio_out; scalar_t__ stdio_in; } ;
typedef  TYPE_1__ process_info_t ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  image ;
typedef  int /*<<< orphan*/  args ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_9__ {scalar_t__ hThread; int /*<<< orphan*/  hProcess; } ;
struct TYPE_8__ {int cb; scalar_t__ hStdError; scalar_t__ hStdOutput; scalar_t__ hStdInput; int /*<<< orphan*/  dwFlags; } ;
typedef  TYPE_2__ STARTUPINFOW ;
typedef  TYPE_3__ PROCESS_INFORMATION ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileA (char*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateFileW (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateProcessW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int FILE_ATTRIBUTE_TEMPORARY ; 
 int FILE_FLAG_DELETE_ON_CLOSE ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 int GetModuleFileNameW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ GetTempFileNameW (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ GetTempPathW (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HANDLE_FLAG_INHERIT ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  STARTF_USESTDHANDLES ; 
 int /*<<< orphan*/  SetHandleInformation (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _snwprintf (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uv_sleep (int) ; 

int process_start(char *name, char *part, process_info_t *p, int is_helper) {
  HANDLE file = INVALID_HANDLE_VALUE;
  HANDLE nul = INVALID_HANDLE_VALUE;
  WCHAR path[MAX_PATH], filename[MAX_PATH];
  WCHAR image[MAX_PATH + 1];
  WCHAR args[MAX_PATH * 2];
  STARTUPINFOW si;
  PROCESS_INFORMATION pi;
  DWORD result;

  if (!is_helper) {
    /* Give the helpers time to settle. Race-y, fix this. */
    uv_sleep(250);
  }

  if (GetTempPathW(sizeof(path) / sizeof(WCHAR), (WCHAR*)&path) == 0)
    goto error;
  if (GetTempFileNameW((WCHAR*)&path, L"uv", 0, (WCHAR*)&filename) == 0)
    goto error;

  file = CreateFileW((WCHAR*)filename,
                     GENERIC_READ | GENERIC_WRITE,
                     0,
                     NULL,
                     CREATE_ALWAYS,
                     FILE_ATTRIBUTE_TEMPORARY | FILE_FLAG_DELETE_ON_CLOSE,
                     NULL);
  if (file == INVALID_HANDLE_VALUE)
    goto error;

  if (!SetHandleInformation(file, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT))
    goto error;

  nul = CreateFileA("nul",
                    GENERIC_READ,
                    FILE_SHARE_READ | FILE_SHARE_WRITE,
                    NULL,
                    OPEN_EXISTING,
                    FILE_ATTRIBUTE_NORMAL,
                    NULL);
  if (nul == INVALID_HANDLE_VALUE)
    goto error;

  if (!SetHandleInformation(nul, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT))
    goto error;

  result = GetModuleFileNameW(NULL,
                              (WCHAR*) &image,
                              sizeof(image) / sizeof(WCHAR));
  if (result == 0 || result == sizeof(image))
    goto error;

  if (part) {
    if (_snwprintf((WCHAR*)args,
                   sizeof(args) / sizeof(WCHAR),
                   L"\"%s\" %S %S",
                   image,
                   name,
                   part) < 0) {
      goto error;
    }
  } else {
    if (_snwprintf((WCHAR*)args,
                   sizeof(args) / sizeof(WCHAR),
                   L"\"%s\" %S",
                   image,
                   name) < 0) {
      goto error;
    }
  }

  memset((void*)&si, 0, sizeof(si));
  si.cb = sizeof(si);
  si.dwFlags = STARTF_USESTDHANDLES;
  si.hStdInput = nul;
  si.hStdOutput = file;
  si.hStdError = file;

  if (!CreateProcessW(image, args, NULL, NULL, TRUE,
                      0, NULL, NULL, &si, &pi))
    goto error;

  CloseHandle(pi.hThread);

  SetHandleInformation(nul, HANDLE_FLAG_INHERIT, 0);
  SetHandleInformation(file, HANDLE_FLAG_INHERIT, 0);

  p->stdio_in = nul;
  p->stdio_out = file;
  p->process = pi.hProcess;
  p->name = part;

  return 0;

error:
  if (file != INVALID_HANDLE_VALUE)
    CloseHandle(file);
  if (nul != INVALID_HANDLE_VALUE)
    CloseHandle(nul);

  return -1;
}