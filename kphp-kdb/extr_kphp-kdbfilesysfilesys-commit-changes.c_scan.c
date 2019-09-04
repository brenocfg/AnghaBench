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

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int clone_file (char const* const,double) ; 
 scalar_t__ compute_tmp_dir_name (char const* const) ; 
 int /*<<< orphan*/  copy_file ; 
 int /*<<< orphan*/  copy_file_cloning_mode ; 
 int /*<<< orphan*/  copy_file_po_mode ; 
 int delete_file (char const* const) ; 
 int /*<<< orphan*/  do_transaction_begin () ; 
 int /*<<< orphan*/  do_transaction_end () ; 
 scalar_t__ events ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ faults ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 scalar_t__ mkdir (double,int) ; 
 double mytime () ; 
 int /*<<< orphan*/  new_dir ; 
 int new_dir_length ; 
 int /*<<< orphan*/  old_dir ; 
 int old_dir_length ; 
 int /*<<< orphan*/  pending_operations_apply () ; 
 int /*<<< orphan*/  pending_operations_init (double,char const* const) ; 
 int /*<<< orphan*/  pending_operations_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rec_scan (int,int,int*) ; 
 int rename (double,char const* const) ; 
 scalar_t__ rmdir (double) ; 
 scalar_t__ status ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const* const) ; 
 int strlen (char const* const) ; 
 double tmp_dir ; 
 scalar_t__ use_clone ; 
 int /*<<< orphan*/  vkprintf (int,char*,double) ; 

__attribute__((used)) static int scan (const char *const old, const char *const new) {
  faults = 0;
  if (!status) {
    if (compute_tmp_dir_name (old) < 0) {
      kprintf ("compute_tmp_dir_name fail.\n");
      exit (1);
    }
    vkprintf (1, "Temporary directory name: %s\n", tmp_dir);
    if (use_clone) {
      double t = -mytime ();
      int r = clone_file (old, tmp_dir);
      if (r < 0) {
        kprintf ("clone_file (%s, %s) returns error code %d.\n", old, tmp_dir, r);
        exit (1);
      }
      t += mytime ();
      vkprintf (1, "Cloning master copy time = %.6lf seconds.\n", t);
      copy_file = copy_file_cloning_mode;
    } else {
      pending_operations_init (tmp_dir, old);
      pending_operations_reset (0);
      if (mkdir (tmp_dir, 0770) < 0) {
        kprintf ("mkdir (%s, 0770) failed. %m\n", tmp_dir);
        exit (1);
      }
      copy_file = copy_file_po_mode;
    }
    do_transaction_begin ();
  }
  old_dir_length = strlen (old);
  assert (old_dir_length < PATH_MAX-1);
  strcpy (old_dir, old);
  new_dir_length = strlen (new);
  assert (new_dir_length < PATH_MAX-1);
  strcpy (new_dir, new);
  int changed;
  rec_scan (old_dir_length, new_dir_length, &changed);

  if (!status) {
    do_transaction_end ();
    if (!faults) {
      if (use_clone) {
        int r = delete_file (old);
        if (r) {
          kprintf ("delete_file (%s) returns error code %d.\n", old, r);
          return -1;
        }
        r = rename (tmp_dir, old);
        if (r) {
          kprintf ("rename (%s, %s) returns error code %d.\n", tmp_dir, old, r);
          return -2;
        }
      } else {
        pending_operations_apply ();
        if (rmdir (tmp_dir) < 0) {
          kprintf ("rmdir (%s) failed. %m\n", tmp_dir);
        }
      }
    }
  }
  return (faults == 0 && (status || events > 0)) ? 0 : -1;
}