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
struct TYPE_4__ {int use_broadcast; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; int /*<<< orphan*/  sem_signaled; int /*<<< orphan*/  sem_waiting; int /*<<< orphan*/  wait_cond; int /*<<< orphan*/  signal_cond; } ;
typedef  TYPE_1__ worker_config ;
typedef  int /*<<< orphan*/  wait_func ;
typedef  int /*<<< orphan*/  signal_func ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ uv_cond_init (int /*<<< orphan*/ *) ; 
 scalar_t__ uv_mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ uv_sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void worker_config_init(worker_config* wc,
                        int use_broadcast,
                        signal_func signal_f,
                        wait_func wait_f) {
  /* Wipe. */
  memset(wc, 0, sizeof(*wc));

  /* Copy vars. */
  wc->signal_cond = signal_f;
  wc->wait_cond = wait_f;
  wc->use_broadcast = use_broadcast;

  /* Init. */
  ASSERT(0 == uv_sem_init(&wc->sem_waiting, 0));
  ASSERT(0 == uv_sem_init(&wc->sem_signaled, 0));
  ASSERT(0 == uv_cond_init(&wc->cond));
  ASSERT(0 == uv_mutex_init(&wc->mutex));
}