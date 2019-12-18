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
struct TYPE_3__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; } ;
typedef  TYPE_1__ uv_semaphore_t ;
typedef  int /*<<< orphan*/  uv_sem_t ;

/* Variables and functions */
 int /*<<< orphan*/  uv__free (TYPE_1__*) ; 
 int /*<<< orphan*/  uv_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void uv__custom_sem_destroy(uv_sem_t* sem_) {
  uv_semaphore_t* sem;

  sem = *(uv_semaphore_t**)sem_;
  uv_cond_destroy(&sem->cond);
  uv_mutex_destroy(&sem->mutex);
  uv__free(sem);
}