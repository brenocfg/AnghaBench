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
typedef  int /*<<< orphan*/  uv_sem_t ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int UV_EAGAIN ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WAIT_TIMEOUT ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 

int uv_sem_trywait(uv_sem_t* sem) {
  DWORD r = WaitForSingleObject(*sem, 0);

  if (r == WAIT_OBJECT_0)
    return 0;

  if (r == WAIT_TIMEOUT)
    return UV_EAGAIN;

  abort();
  return -1; /* Satisfy the compiler. */
}