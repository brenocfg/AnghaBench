#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  replica_prefix; } ;

/* Variables and functions */
 int /*<<< orphan*/  compression_level ; 
 TYPE_1__* engine_snapshot_replica ; 
 int /*<<< orphan*/  exit (int) ; 
 char* get_new_snapshot_name (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 scalar_t__ last_snapshot_log_pos ; 
 scalar_t__ log_cur_pos () ; 
 int /*<<< orphan*/  print_snapshot_name (char*) ; 
 scalar_t__ rename_temporary_snapshot (char*) ; 
 int save_binlogpos () ; 
 int tar_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  work_dir ; 

int save_index (void) {
  char *newidxname = NULL;

  if (log_cur_pos () == last_snapshot_log_pos) {
    kprintf ("skipping generation of new snapshot (snapshot for this position already exists)\n");
    return 0;
  }

  if (engine_snapshot_replica) {
    newidxname = get_new_snapshot_name (engine_snapshot_replica, log_cur_pos(), engine_snapshot_replica->replica_prefix);
  }

  if (!newidxname || newidxname[0] == '-') {
    kprintf ("cannot write index: cannot compute its name\n");
    exit (1);
  }
  int r = save_binlogpos ();
  if (r < 0) {
    kprintf ("save_binlogpos returns error code %d.\n", r);
    exit (1);
  }
  r = tar_pack (newidxname, work_dir, compression_level);
  if (r < 0) {
    kprintf ("tar_pack (%s, %s, %d) return error code %d.\n", newidxname, work_dir, compression_level, r);
    exit (1);
  }

  if (rename_temporary_snapshot (newidxname)) {
    kprintf ("cannot rename new index file from %s: %m\n", newidxname);
    unlink (newidxname);
    exit (1);
  }

  print_snapshot_name (newidxname);

  last_snapshot_log_pos = log_cur_pos (); /* guard: don't save index twice for same_log_pos */
  return 0;
}