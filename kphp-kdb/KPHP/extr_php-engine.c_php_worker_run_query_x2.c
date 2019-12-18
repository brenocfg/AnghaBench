#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  php_worker ;
struct TYPE_5__ {TYPE_3__* ans; } ;
struct TYPE_6__ {int val; TYPE_1__ base; } ;
typedef  TYPE_2__ php_query_x2_t ;
struct TYPE_7__ {int x2; } ;
typedef  TYPE_3__ php_query_x2_answer_t ;

/* Variables and functions */
 int /*<<< orphan*/  php_script ; 
 int /*<<< orphan*/  php_script_query_answered (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_script_query_readed (int /*<<< orphan*/ ) ; 

void php_worker_run_query_x2 (php_worker *worker, php_query_x2_t *query) {
  php_script_query_readed (php_script);

//  worker->conn->status = conn_wait_net;
//  worker->conn->pending_queries = 1;

  static php_query_x2_answer_t res;
  res.x2 = query->val * query->val;

  query->base.ans = &res;

  php_script_query_answered (php_script);
}