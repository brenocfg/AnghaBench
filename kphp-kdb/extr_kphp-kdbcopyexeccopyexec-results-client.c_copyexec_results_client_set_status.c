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
struct results_queue_entry {unsigned int result; int /*<<< orphan*/  transaction_id; int /*<<< orphan*/  binlog_pos; } ;
struct lev_copyexec_main_transaction_status {int result; int /*<<< orphan*/  transaction_id; scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ LEV_COPYEXEC_MAIN_TRANSACTION_STATUS ; 
 int /*<<< orphan*/  log_cur_pos () ; 
 struct results_queue_entry* results_queue_push () ; 
 int /*<<< orphan*/  vkprintf (int,char*) ; 

int copyexec_results_client_set_status (struct lev_copyexec_main_transaction_status *E) {
  struct results_queue_entry *A = results_queue_push ();
  if (A == NULL) {
    vkprintf (3, "Results queue full. Stop binlog replaying.\n");
    return -1;
  }
  A->binlog_pos = log_cur_pos ();
  A->result = (((unsigned)(E->type - LEV_COPYEXEC_MAIN_TRANSACTION_STATUS)) << 28) | (E->result & 0x0fffffff);
  A->transaction_id = E->transaction_id;

  return 0;
}