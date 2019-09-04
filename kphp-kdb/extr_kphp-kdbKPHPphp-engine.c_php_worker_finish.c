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
struct TYPE_4__ {scalar_t__ target_fd; double start_time; int /*<<< orphan*/  req_id; } ;
typedef  TYPE_1__ php_worker ;

/* Variables and functions */
 scalar_t__ lease_state ; 
 int /*<<< orphan*/  lease_stats_cnt ; 
 double lease_stats_time ; 
 scalar_t__ lst_finish ; 
 scalar_t__ lst_on ; 
 int /*<<< orphan*/  php_worker_free (TYPE_1__*) ; 
 double precise_now ; 
 scalar_t__ rpc_lease_target ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ) ; 

void php_worker_finish (php_worker *worker) {
  vkprintf (2, "free php script [req_id = %016llx]\n", worker->req_id);
  if ((lease_state == lst_on || lease_state == lst_finish) && worker->target_fd == rpc_lease_target) {
    double worked = precise_now - worker->start_time;
    lease_stats_time += worked;
    lease_stats_cnt++;
  }

  php_worker_free (worker);
}