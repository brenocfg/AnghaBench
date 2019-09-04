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
struct TYPE_2__ {int posted; int /*<<< orphan*/  mutex; int /*<<< orphan*/  sem; scalar_t__ delay; } ;
typedef  TYPE_1__ worker_config ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  uv_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_sem_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_sleep (scalar_t__) ; 

__attribute__((used)) static void worker(void* arg) {
  worker_config* c = arg;

  if (c->delay)
    uv_sleep(c->delay);

  uv_mutex_lock(&c->mutex);
  ASSERT(c->posted == 0);
  uv_sem_post(&c->sem);
  c->posted = 1;
  uv_mutex_unlock(&c->mutex);
}