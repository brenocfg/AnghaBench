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
struct lev_filesys_rmdir {int dirpath_size; int /*<<< orphan*/  dirpath; } ;
struct TYPE_3__ {int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ file_t ;

/* Variables and functions */
 int /*<<< orphan*/  LEV_FILESYS_XFS_FILE_REMOVE ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  append_path (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int delete_file (char*) ; 
 int /*<<< orphan*/  faults ; 
 struct lev_filesys_rmdir* filesys_xfs_alloc_log_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kprintf (char*,char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int const) ; 
 char* old_dir ; 
 int old_dir_length ; 
 int /*<<< orphan*/  pending_operation_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pending_operation_push (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pot_remove ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int snprintf (char*,int,char*,char*,char*) ; 
 scalar_t__ status ; 
 int strlen (char*) ; 
 char* tmp_dir ; 
 scalar_t__ use_clone ; 
 int /*<<< orphan*/  vkprintf (int,char*,char*) ; 

void remove_file (int l, file_t *x) {
  char *local_path = old_dir + old_dir_length + 1;
  append_path (old_dir, l, x->filename);
  vkprintf (3, "Remove: %s\n", local_path);
  if (status) {
    printf ("Remove: %s\n", local_path);
  } else {
    char a[PATH_MAX];
    int r = 0;
    assert (snprintf (a, PATH_MAX, "%s/%s", tmp_dir, local_path) < PATH_MAX);
    if (use_clone) {
      r = delete_file (a);
    } else {
      pending_operation_push (pending_operation_create (pot_remove, NULL, local_path, NULL));
    }
    if (!r) {
      const int name_length = strlen (local_path);
      struct lev_filesys_rmdir *E = filesys_xfs_alloc_log_event (LEV_FILESYS_XFS_FILE_REMOVE, sizeof (struct lev_filesys_rmdir) + name_length);
      E->dirpath_size = name_length;
      memcpy (E->dirpath, local_path, name_length);
    } else {
      kprintf ("delete_file (%s/%s) failed (exit_code = %d).\n", tmp_dir, local_path, r);
      faults++;
    }
  }
  old_dir[l] = 0;
}