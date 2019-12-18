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
struct binlog_wait_query {int /*<<< orphan*/  (* on_complete ) (struct binlog_wait_query*) ;struct binlog_wait_query* x; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct binlog_wait_query*) ; 
 int /*<<< orphan*/  binlog_wait_time_tree ; 
 scalar_t__ lookup_binlog_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next_binlog_wait_time ; 
 int /*<<< orphan*/  stub1 (struct binlog_wait_query*) ; 
 int /*<<< orphan*/  tl_update_next_binlog_wait_time () ; 
 int /*<<< orphan*/  tree_delete_binlog_wait (int /*<<< orphan*/ ,struct binlog_wait_query*) ; 
 struct binlog_wait_query* tree_get_min_binlog_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (struct binlog_wait_query*,int) ; 

void tl_binlog_wait_time_restart_all_finished (void) {
  while (lookup_binlog_time (next_binlog_wait_time) > 0) {
    assert (tree_get_min_binlog_wait (binlog_wait_time_tree));
    struct binlog_wait_query *Q = tree_get_min_binlog_wait (binlog_wait_time_tree)->x;
    assert (Q);
    Q->on_complete (Q);
    binlog_wait_time_tree = tree_delete_binlog_wait (binlog_wait_time_tree, Q);
    tl_update_next_binlog_wait_time ();
    zfree (Q, sizeof (*Q));
  }
}