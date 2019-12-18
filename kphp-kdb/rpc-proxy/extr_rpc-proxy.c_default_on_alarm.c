#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rpc_query {scalar_t__ start_time; int /*<<< orphan*/  old_qid; int /*<<< orphan*/  pid; int /*<<< orphan*/  in_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  TL_ERROR_QUERY_TIMEOUT ; 
 scalar_t__ precise_now ; 
 int /*<<< orphan*/  rpc_answers_timedout ; 
 int /*<<< orphan*/  timeouted_queries ; 
 int /*<<< orphan*/  tl_fetch_set_error_format (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ tl_init_store (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_store_end () ; 

void default_on_alarm (struct rpc_query *q) {
  timeouted_queries ++;
  rpc_answers_timedout ++;
  if (tl_init_store (q->in_type, /*q->in,*/  &q->pid, q->old_qid) >= 0) {
    tl_fetch_set_error_format (TL_ERROR_QUERY_TIMEOUT, "Query timeout: working_time = %lf", precise_now - q->start_time);
    tl_store_end ();
  }
//  delete_rpc_query (q);
}