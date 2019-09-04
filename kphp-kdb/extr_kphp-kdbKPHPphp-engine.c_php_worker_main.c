#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int state; TYPE_1__* conn; scalar_t__ paused; } ;
typedef  TYPE_2__ php_worker ;
struct TYPE_9__ {scalar_t__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ conn_wait_net ; 
 int /*<<< orphan*/  php_worker_finish (TYPE_2__*) ; 
 int /*<<< orphan*/  php_worker_free_script (TYPE_2__*) ; 
 int /*<<< orphan*/  php_worker_init_script (TYPE_2__*) ; 
 int /*<<< orphan*/  php_worker_run (TYPE_2__*) ; 
 int /*<<< orphan*/  php_worker_try_start (TYPE_2__*) ; 
#define  phpq_finish 132 
#define  phpq_free_script 131 
#define  phpq_init_script 130 
#define  phpq_run 129 
#define  phpq_try_start 128 

int php_worker_main (php_worker *worker) {
  worker->paused = 0;
  do {
    switch (worker->state) {
      case phpq_try_start:
        php_worker_try_start (worker);
        break;

      case phpq_init_script:
        php_worker_init_script (worker);
        break;

      case phpq_run:
        php_worker_run (worker);
        break;

      case phpq_free_script:
        php_worker_free_script (worker);
        break;

      case phpq_finish:
        php_worker_finish (worker);
        return 1;
    }
  } while (!worker->paused);

  assert (worker->conn->status == conn_wait_net);
  return 0;
}