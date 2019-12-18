#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int value; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; } ;
typedef  TYPE_1__ uv_semaphore_t ;
typedef  int /*<<< orphan*/  uv_sem_t ;

/* Variables and functions */
 int UV_ENOMEM ; 
 int /*<<< orphan*/  uv__free (TYPE_1__*) ; 
 TYPE_1__* uv__malloc (int) ; 
 int uv_cond_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_mutex_destroy (int /*<<< orphan*/ *) ; 
 int uv_mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int uv__custom_sem_init(uv_sem_t* sem_, unsigned int value) {
  int err;
  uv_semaphore_t* sem;

  sem = uv__malloc(sizeof(*sem));
  if (sem == NULL)
    return UV_ENOMEM;

  if ((err = uv_mutex_init(&sem->mutex)) != 0) {
    uv__free(sem);
    return err;
  }

  if ((err = uv_cond_init(&sem->cond)) != 0) {
    uv_mutex_destroy(&sem->mutex);
    uv__free(sem);
    return err;
  }

  sem->value = value;
  *(uv_semaphore_t**)sem_ = sem;
  return 0;
}