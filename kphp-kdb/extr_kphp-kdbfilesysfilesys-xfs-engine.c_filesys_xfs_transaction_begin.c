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
struct lev_filesys_xfs_transaction {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  delete_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ ) ; 
 int mkdir (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pending_operations_reset (int) ; 
 scalar_t__ pending_saving_binlogpos_logpos ; 
 int /*<<< orphan*/  tmp_dir ; 
 scalar_t__ transaction_file_no ; 
 int /*<<< orphan*/  transaction_id ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void filesys_xfs_transaction_begin (struct lev_filesys_xfs_transaction *E) {
  pending_saving_binlogpos_logpos = 0;
  vkprintf (1, "Begin transaction %d.\n", E->id);
  int r = 0;
  pending_operations_reset (1);
  delete_file (tmp_dir);
  r = mkdir (tmp_dir, 0777);
  if (r < 0) {
    kprintf ("mkdir (%s) fail. %m\n", tmp_dir);
    exit (1);
  }
  transaction_id = E->id;
  transaction_file_no = 0;
}