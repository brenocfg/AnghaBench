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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  build_pairs_from_text () ; 
 int /*<<< orphan*/  build_word_lists () ; 
 scalar_t__ close (int /*<<< orphan*/ ) ; 
 TYPE_1__* engine_snapshot_replica ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/ * fd ; 
 int /*<<< orphan*/  flushout () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fsync (int /*<<< orphan*/ ) ; 
 char* get_new_snapshot_name (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kprintf (char*,char*) ; 
 int /*<<< orphan*/  log_cur_pos () ; 
 char* newidxname ; 
 int /*<<< orphan*/  open_file (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  print_snapshot_name (char*) ; 
 scalar_t__ rename_temporary_snapshot (char*) ; 
 int /*<<< orphan*/  set_read_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_write_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sort_items () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  write_header0 () ; 
 int /*<<< orphan*/  write_header1 () ; 
 int /*<<< orphan*/  write_text () ; 

void save_index (void) {
  if (engine_snapshot_replica) {
    newidxname = get_new_snapshot_name (engine_snapshot_replica, log_cur_pos(), engine_snapshot_replica->replica_prefix);
  }

  if (!newidxname || newidxname[0] == '-') {
    fprintf (stderr, "cannot write index: cannot compute its name\n");
    exit (1);
  }

  open_file (0, newidxname, 1);

  set_read_file (fd[0]);
  set_write_file (fd[0]);

  sort_items ();

  write_header0 ();
  write_text ();
  build_pairs_from_text ();
  build_word_lists ();
  write_header1 ();

  flushout ();

  assert (fsync(fd[0]) >= 0);
  assert (close (fd[0]) >= 0);

  if (rename_temporary_snapshot (newidxname)) {
    kprintf ("cannot rename new index file from %s: %m\n", newidxname);
    unlink (newidxname);
    exit (1);
  }

  print_snapshot_name (newidxname);
}