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
struct lev_copyexec_result_data {int result; int /*<<< orphan*/  binlog_pos; int /*<<< orphan*/  transaction_id; int /*<<< orphan*/  random_tag; } ;

/* Variables and functions */
 scalar_t__ dump_line_header (char*) ; 
 int /*<<< orphan*/  dump_result (int,int) ; 
 int /*<<< orphan*/  dump_ts (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  out ; 

__attribute__((used)) static void dump_data (struct lev_copyexec_result_data *E) {
  if (dump_line_header ("LEV_COPYEXEC_RESULT_DATA")) {
    return;
  }
  fprintf (out, "0x%llx\t%d\t", E->random_tag, E->transaction_id);
  int status = E->result >> 28, result = E->result & 0x0fffffff;
  dump_ts (status);
  fprintf (out, "\t");
  dump_result (status, result);
  fprintf (out, "\t%lld\n", E->binlog_pos);
}