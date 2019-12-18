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
struct TYPE_3__ {unsigned int n; int /*<<< orphan*/  mutex; int /*<<< orphan*/  turnstile1; int /*<<< orphan*/  turnstile2; scalar_t__ count; } ;
typedef  TYPE_1__ uv_barrier_t ;

/* Variables and functions */
 int /*<<< orphan*/  uv_mutex_destroy (int /*<<< orphan*/ *) ; 
 int uv_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_sem_destroy (int /*<<< orphan*/ *) ; 
 int uv_sem_init (int /*<<< orphan*/ *,int) ; 

int uv_barrier_init(uv_barrier_t* barrier, unsigned int count) {
  int err;

  barrier->n = count;
  barrier->count = 0;

  err = uv_mutex_init(&barrier->mutex);
  if (err)
    return err;

  err = uv_sem_init(&barrier->turnstile1, 0);
  if (err)
    goto error2;

  err = uv_sem_init(&barrier->turnstile2, 1);
  if (err)
    goto error;

  return 0;

error:
  uv_sem_destroy(&barrier->turnstile1);
error2:
  uv_mutex_destroy(&barrier->mutex);
  return err;

}