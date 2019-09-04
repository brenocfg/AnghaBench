#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  script_t ;
struct TYPE_4__ {double finish_time; double start_time; int /*<<< orphan*/  state; int /*<<< orphan*/  data; int /*<<< orphan*/  req_id; scalar_t__ terminate_flag; } ;
typedef  TYPE_1__ php_worker ;
struct TYPE_5__ {int is_running; scalar_t__ is_wait_net; } ;

/* Variables and functions */
 int /*<<< orphan*/  dl_assert (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * get_script (char*) ; 
 int /*<<< orphan*/  get_utime_monotonic () ; 
 TYPE_3__ immediate_stats ; 
 scalar_t__ max_memory ; 
 int /*<<< orphan*/ * php_script ; 
 int /*<<< orphan*/ * php_script_create (size_t,size_t) ; 
 int /*<<< orphan*/  php_script_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_script_set_timeout (double) ; 
 int /*<<< orphan*/  phpq_finish ; 
 int /*<<< orphan*/  phpq_run ; 
 double precise_now ; 
 int /*<<< orphan*/  qmem_init () ; 
 int /*<<< orphan*/  qresults_clean () ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ) ; 

void php_worker_init_script (php_worker *worker) {
  double timeout = worker->finish_time - precise_now - 0.01;
  if (worker->terminate_flag || timeout < 0.2) {
    worker->state = phpq_finish;
    return;
  }

  /*if (http_sfd != -1) {*/
    /*epoll_remove (http_sfd);*/
  /*}*/

  get_utime_monotonic();
  worker->start_time = precise_now;
  vkprintf (1, "START php script [req_id = %016llx]\n", worker->req_id);
  immediate_stats.is_running = 1;
  immediate_stats.is_wait_net = 0;

  //init memory allocator for queries
  qmem_init();
  qresults_clean();

  script_t *script = get_script ("#0");
  dl_assert (script != NULL, "failed to get script");
  if (php_script == NULL) {
    php_script = php_script_create ((size_t)max_memory, (size_t)(8 << 20));
  }
  php_script_init (php_script, script, worker->data);
  php_script_set_timeout (timeout);
  worker->state = phpq_run;
}