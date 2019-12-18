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
struct TYPE_6__ {int protocol; TYPE_1__ base; int /*<<< orphan*/  port; int /*<<< orphan*/  host; } ;
typedef  TYPE_2__ php_query_connect_t ;
struct TYPE_7__ {void* connection_id; } ;
typedef  TYPE_3__ php_query_connect_answer_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_ct ; 
 void* get_target (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
#define  p_memcached 130 
#define  p_rpc 129 
#define  p_sql 128 
 int /*<<< orphan*/  php_script ; 
 int /*<<< orphan*/  php_script_query_answered (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_script_query_readed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_ct ; 
 void* sql_target_id ; 

void php_worker_run_query_connect (php_worker *worker, php_query_connect_t *query) {
  php_script_query_readed (php_script);

  static php_query_connect_answer_t res;

  switch (query->protocol) {
    case p_memcached:
      res.connection_id = get_target (query->host, query->port, &default_ct);
      break;
    case p_sql:
      res.connection_id = sql_target_id;
      break;
    case p_rpc:
      res.connection_id = get_target (query->host, query->port, &rpc_ct);
      break;
    default:
      assert ("unknown protocol" && 0);
  }

  query->base.ans = &res;

  php_script_query_answered (php_script);
}