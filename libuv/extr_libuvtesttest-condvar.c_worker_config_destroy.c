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
struct TYPE_3__ {int /*<<< orphan*/  sem_waiting; int /*<<< orphan*/  sem_signaled; int /*<<< orphan*/  cond; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ worker_config ;

/* Variables and functions */
 int /*<<< orphan*/  uv_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_sem_destroy (int /*<<< orphan*/ *) ; 

void worker_config_destroy(worker_config* wc) {
  uv_mutex_destroy(&wc->mutex);
  uv_cond_destroy(&wc->cond);
  uv_sem_destroy(&wc->sem_signaled);
  uv_sem_destroy(&wc->sem_waiting);
}