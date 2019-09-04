#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ value; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ uv_semaphore_t ;
typedef  int /*<<< orphan*/  uv_sem_t ;

/* Variables and functions */
 int UV_EAGAIN ; 
 scalar_t__ uv_mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int uv__custom_sem_trywait(uv_sem_t* sem_) {
  uv_semaphore_t* sem;

  sem = *(uv_semaphore_t**)sem_;
  if (uv_mutex_trylock(&sem->mutex) != 0)
    return UV_EAGAIN;

  if (sem->value == 0) {
    uv_mutex_unlock(&sem->mutex);
    return UV_EAGAIN;
  }

  sem->value--;
  uv_mutex_unlock(&sem->mutex);

  return 0;
}