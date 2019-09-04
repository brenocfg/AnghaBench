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
struct TYPE_3__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  turnstile1; int /*<<< orphan*/  turnstile2; } ;
typedef  TYPE_1__ uv_barrier_t ;

/* Variables and functions */
 int /*<<< orphan*/  uv_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_sem_destroy (int /*<<< orphan*/ *) ; 

void uv_barrier_destroy(uv_barrier_t* barrier) {
  uv_sem_destroy(&barrier->turnstile2);
  uv_sem_destroy(&barrier->turnstile1);
  uv_mutex_destroy(&barrier->mutex);
}