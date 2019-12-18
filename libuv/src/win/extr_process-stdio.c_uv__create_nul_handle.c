#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int nLength; int /*<<< orphan*/  bInheritHandle; int /*<<< orphan*/ * lpSecurityDescriptor; } ;
typedef  TYPE_1__ SECURITY_ATTRIBUTES ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ CreateFileW (char*,int /*<<< orphan*/ ,int,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  TRUE ; 

int uv__create_nul_handle(HANDLE* handle_ptr,
    DWORD access) {
  HANDLE handle;
  SECURITY_ATTRIBUTES sa;

  sa.nLength = sizeof sa;
  sa.lpSecurityDescriptor = NULL;
  sa.bInheritHandle = TRUE;

  handle = CreateFileW(L"NUL",
                       access,
                       FILE_SHARE_READ | FILE_SHARE_WRITE,
                       &sa,
                       OPEN_EXISTING,
                       0,
                       NULL);
  if (handle == INVALID_HANDLE_VALUE) {
    return GetLastError();
  }

  *handle_ptr = handle;
  return 0;
}