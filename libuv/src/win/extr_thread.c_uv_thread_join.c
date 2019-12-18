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
typedef  scalar_t__ uv_thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  MemoryBarrier () ; 
 scalar_t__ WaitForSingleObject (scalar_t__,int /*<<< orphan*/ ) ; 
 int uv_translate_sys_error (int /*<<< orphan*/ ) ; 

int uv_thread_join(uv_thread_t *tid) {
  if (WaitForSingleObject(*tid, INFINITE))
    return uv_translate_sys_error(GetLastError());
  else {
    CloseHandle(*tid);
    *tid = 0;
    MemoryBarrier();  /* For feature parity with pthread_join(). */
    return 0;
  }
}