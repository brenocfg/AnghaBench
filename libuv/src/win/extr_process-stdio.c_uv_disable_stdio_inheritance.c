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
struct TYPE_3__ {int /*<<< orphan*/  lpReserved2; int /*<<< orphan*/  cbReserved2; } ;
typedef  TYPE_1__ STARTUPINFOW ;
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  GetStartupInfoW (TYPE_1__*) ; 
 int /*<<< orphan*/ * GetStdHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HANDLE_FLAG_INHERIT ; 
 int /*<<< orphan*/ * INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  STD_ERROR_HANDLE ; 
 int /*<<< orphan*/  STD_INPUT_HANDLE ; 
 int /*<<< orphan*/  STD_OUTPUT_HANDLE ; 
 int /*<<< orphan*/  SetHandleInformation (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__stdio_noinherit (int /*<<< orphan*/ ) ; 
 scalar_t__ uv__stdio_verify (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void uv_disable_stdio_inheritance(void) {
  HANDLE handle;
  STARTUPINFOW si;

  /* Make the windows stdio handles non-inheritable. */
  handle = GetStdHandle(STD_INPUT_HANDLE);
  if (handle != NULL && handle != INVALID_HANDLE_VALUE)
    SetHandleInformation(handle, HANDLE_FLAG_INHERIT, 0);

  handle = GetStdHandle(STD_OUTPUT_HANDLE);
  if (handle != NULL && handle != INVALID_HANDLE_VALUE)
    SetHandleInformation(handle, HANDLE_FLAG_INHERIT, 0);

  handle = GetStdHandle(STD_ERROR_HANDLE);
  if (handle != NULL && handle != INVALID_HANDLE_VALUE)
    SetHandleInformation(handle, HANDLE_FLAG_INHERIT, 0);

  /* Make inherited CRT FDs non-inheritable. */
  GetStartupInfoW(&si);
  if (uv__stdio_verify(si.lpReserved2, si.cbReserved2))
    uv__stdio_noinherit(si.lpReserved2);
}