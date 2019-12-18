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
typedef  int /*<<< orphan*/  uv_pid_t ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int ABOVE_NORMAL_PRIORITY_CLASS ; 
 int BELOW_NORMAL_PRIORITY_CLASS ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int GetPriorityClass (int /*<<< orphan*/ ) ; 
 int HIGH_PRIORITY_CLASS ; 
 int NORMAL_PRIORITY_CLASS ; 
 int /*<<< orphan*/  PROCESS_QUERY_LIMITED_INFORMATION ; 
 int REALTIME_PRIORITY_CLASS ; 
 int UV_EINVAL ; 
 int UV_PRIORITY_ABOVE_NORMAL ; 
 int UV_PRIORITY_BELOW_NORMAL ; 
 int UV_PRIORITY_HIGH ; 
 int UV_PRIORITY_HIGHEST ; 
 int UV_PRIORITY_LOW ; 
 int UV_PRIORITY_NORMAL ; 
 int uv__get_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int uv_translate_sys_error (int /*<<< orphan*/ ) ; 

int uv_os_getpriority(uv_pid_t pid, int* priority) {
  HANDLE handle;
  int r;

  if (priority == NULL)
    return UV_EINVAL;

  r = uv__get_handle(pid, PROCESS_QUERY_LIMITED_INFORMATION, &handle);

  if (r != 0)
    return r;

  r = GetPriorityClass(handle);

  if (r == 0) {
    r = uv_translate_sys_error(GetLastError());
  } else {
    /* Map Windows priority classes to Unix nice values. */
    if (r == REALTIME_PRIORITY_CLASS)
      *priority = UV_PRIORITY_HIGHEST;
    else if (r == HIGH_PRIORITY_CLASS)
      *priority = UV_PRIORITY_HIGH;
    else if (r == ABOVE_NORMAL_PRIORITY_CLASS)
      *priority = UV_PRIORITY_ABOVE_NORMAL;
    else if (r == NORMAL_PRIORITY_CLASS)
      *priority = UV_PRIORITY_NORMAL;
    else if (r == BELOW_NORMAL_PRIORITY_CLASS)
      *priority = UV_PRIORITY_BELOW_NORMAL;
    else  /* IDLE_PRIORITY_CLASS */
      *priority = UV_PRIORITY_LOW;

    r = 0;
  }

  CloseHandle(handle);
  return r;
}