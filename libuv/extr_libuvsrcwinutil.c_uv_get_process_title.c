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

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int UV_EINVAL ; 
 int UV_ENOBUFS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  process_title ; 
 int /*<<< orphan*/  process_title_lock ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int uv__get_process_title () ; 
 int /*<<< orphan*/  uv__once_init () ; 
 int uv_translate_sys_error (int /*<<< orphan*/ ) ; 

int uv_get_process_title(char* buffer, size_t size) {
  size_t len;

  if (buffer == NULL || size == 0)
    return UV_EINVAL;

  uv__once_init();

  EnterCriticalSection(&process_title_lock);
  /*
   * If the process_title was never read before nor explicitly set,
   * we must query it with getConsoleTitleW
   */
  if (!process_title && uv__get_process_title() == -1) {
    LeaveCriticalSection(&process_title_lock);
    return uv_translate_sys_error(GetLastError());
  }

  assert(process_title);
  len = strlen(process_title) + 1;

  if (size < len) {
    LeaveCriticalSection(&process_title_lock);
    return UV_ENOBUFS;
  }

  memcpy(buffer, process_title, len);
  LeaveCriticalSection(&process_title_lock);

  return 0;
}