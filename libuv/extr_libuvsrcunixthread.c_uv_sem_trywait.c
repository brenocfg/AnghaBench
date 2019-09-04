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
 scalar_t__ platform_needs_custom_semaphore ; 
 int uv__custom_sem_trywait (int /*<<< orphan*/ *) ; 
 int uv__sem_trywait (int /*<<< orphan*/ *) ; 

int uv_sem_trywait(uv_sem_t* sem) {
  if (platform_needs_custom_semaphore)
    return uv__custom_sem_trywait(sem);
  else
    return uv__sem_trywait(sem);
}