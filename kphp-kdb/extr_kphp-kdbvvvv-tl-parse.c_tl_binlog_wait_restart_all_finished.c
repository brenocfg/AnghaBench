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
struct binlog_wait_query {int /*<<< orphan*/  (* on_complete ) (struct binlog_wait_query*) ;} ;
struct TYPE_2__ {struct binlog_wait_query* x; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct binlog_wait_query*) ; 
 int /*<<< orphan*/  binlog_wait_tree ; 
 long long log_last_pos () ; 
 long long next_binlog_wait_pos ; 
 int /*<<< orphan*/  stub1 (struct binlog_wait_query*) ; 
 int /*<<< orphan*/  tl_update_next_binlog_wait_pos () ; 
 int /*<<< orphan*/  tree_delete_binlog_wait (int /*<<< orphan*/ ,struct binlog_wait_query*) ; 
 TYPE_1__* tree_get_min_binlog_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (struct binlog_wait_query*,int) ; 

void tl_binlog_wait_restart_all_finished (void) {
  long long cur_pos = log_last_pos ();
//  vkprintf (2, "cur_pos = %lld, next_pos = %lld\n", cur_pos, next_binlog_wait_pos);
  while (cur_pos >= next_binlog_wait_pos) {
    struct binlog_wait_query *Q = tree_get_min_binlog_wait (binlog_wait_tree)->x;
    assert (Q);
    Q->on_complete (Q);
    binlog_wait_tree = tree_delete_binlog_wait (binlog_wait_tree, Q);
    tl_update_next_binlog_wait_pos ();
    zfree (Q, sizeof (*Q));
  }
}