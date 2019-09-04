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
struct lev_copyexec_main_transaction_status {int type; int transaction_id; int /*<<< orphan*/  st_ino; int /*<<< orphan*/  st_dev; int /*<<< orphan*/  result; int /*<<< orphan*/  creation_time; int /*<<< orphan*/  pid; int /*<<< orphan*/  mask; int /*<<< orphan*/  binlog_pos; } ;

/* Variables and functions */
 scalar_t__ dump_line_header (char*) ; 
 int /*<<< orphan*/  dump_result (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_ts (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  out ; 

void dump_status (struct lev_copyexec_main_transaction_status *E) {
  int status = E->type & 255;
  if (dump_line_header ("LEV_COPYEXEC_MAIN_TRANSACTION_STATUS")) {
    return;
  }
  dump_ts (E->type);
  fprintf (out, "\t%d\t%lld\t0x%x\t%d\t%d\t", E->transaction_id, E->binlog_pos, E->mask, E->pid, E->creation_time);
  dump_result (status, E->result);
  fprintf (out, "\t%lld\t%lld\n", E->st_dev, E->st_ino);
}