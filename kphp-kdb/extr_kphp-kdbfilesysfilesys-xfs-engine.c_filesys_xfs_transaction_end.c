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
struct lev_filesys_xfs_transaction {scalar_t__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  delete_file (int /*<<< orphan*/ ) ; 
 scalar_t__ last_closed_transaction_id ; 
 int /*<<< orphan*/  last_closed_transaction_time ; 
 scalar_t__ log_cur_pos () ; 
 int /*<<< orphan*/  now ; 
 int /*<<< orphan*/  pending_operations_apply () ; 
 scalar_t__ pending_saving_binlogpos_logpos ; 
 int /*<<< orphan*/  tmp_dir ; 
 scalar_t__ transaction_id ; 

__attribute__((used)) static void filesys_xfs_transaction_end (struct lev_filesys_xfs_transaction *E) {
  assert (transaction_id == E->id);
  pending_operations_apply ();
  delete_file (tmp_dir);
  pending_saving_binlogpos_logpos = log_cur_pos () + 8;
  last_closed_transaction_id = transaction_id;
  last_closed_transaction_time = now;
}