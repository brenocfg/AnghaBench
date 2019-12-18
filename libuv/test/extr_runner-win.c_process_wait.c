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
struct TYPE_3__ {int /*<<< orphan*/  process; } ;
typedef  TYPE_1__ process_info_t ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ INFINITE ; 
 int MAXIMUM_WAIT_OBJECTS ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WAIT_TIMEOUT ; 
 scalar_t__ WaitForMultipleObjects (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

int process_wait(process_info_t *vec, int n, int timeout) {
  int i;
  HANDLE handles[MAXIMUM_WAIT_OBJECTS];
  DWORD timeout_api, result;

  /* If there's nothing to wait for, return immediately. */
  if (n == 0)
    return 0;

  ASSERT(n <= MAXIMUM_WAIT_OBJECTS);

  for (i = 0; i < n; i++)
    handles[i] = vec[i].process;

  if (timeout >= 0) {
    timeout_api = (DWORD)timeout;
  } else {
    timeout_api = INFINITE;
  }

  result = WaitForMultipleObjects(n, handles, TRUE, timeout_api);

  if (result < WAIT_OBJECT_0 + n) {
    /* All processes are terminated. */
    return 0;
  }
  if (result == WAIT_TIMEOUT) {
    return -2;
  }
  return -1;
}