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

/* Variables and functions */
 int /*<<< orphan*/  INFINITE ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 

void uv_sem_wait(uv_sem_t* sem) {
  if (WaitForSingleObject(*sem, INFINITE) != WAIT_OBJECT_0)
    abort();
}