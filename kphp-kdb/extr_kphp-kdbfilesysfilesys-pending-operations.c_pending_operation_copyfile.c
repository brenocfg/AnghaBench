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
struct static_pending_operation {int dummy; } ;
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  enum pending_operation_tp { ____Placeholder_pending_operation_tp } pending_operation_tp ;
typedef  scalar_t__ dyn_mark_t ;

/* Variables and functions */
 int O_CREAT ; 
 int O_EXCL ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int PATH_MAX ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  compute_temporary_filename (int,int*,char const* const,char*) ; 
 int /*<<< orphan*/  dyn_release (scalar_t__) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  kprintf (char*,char*) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  pending_operation_create (int,char*,char const* const,struct stat*) ; 
 int /*<<< orphan*/  pending_operation_fill (struct static_pending_operation*,int,char*,char const* const,struct stat*) ; 
 int /*<<< orphan*/  pending_operation_push (int /*<<< orphan*/ ) ; 
 int po_olddir_length ; 
 int pot_mkdir ; 
 int pot_rename ; 
 int pot_symlink ; 
 int /*<<< orphan*/  vkprintf (int,char*,char*) ; 
 int write (int,void*,int) ; 

void pending_operation_copyfile (int transaction_id, int *transaction_file_no, const char *const name, void *data, int data_size, struct stat *S, struct static_pending_operation *P, dyn_mark_t release_mark) {
  enum pending_operation_tp type;
  char *oldpath;
  if (S_ISLNK (S->st_mode)) {
    type = pot_symlink;
    oldpath = (char *) data;
  } else if (S_ISDIR (S->st_mode)) {
    type = pot_mkdir;
    oldpath = NULL;
  } else {
    char full_tmp_filename[PATH_MAX];
    compute_temporary_filename (transaction_id, transaction_file_no, name, full_tmp_filename);
    vkprintf (4, "full_tmp_filename = %s\n", full_tmp_filename);
    int fd = open (full_tmp_filename, O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, 0660);
    if (fd < 0) {
      kprintf ("fail to open file '%s', flags: O_CREAT | O_TRUNC | O_WRONLY | O_EXCL. %m\n", full_tmp_filename);
      exit (1);
    }
    assert (fd >= 0);
    assert (data_size == write (fd, data, data_size));
    assert (!close (fd));
    type = pot_rename;
    oldpath = full_tmp_filename + po_olddir_length + 1;
  }
  if (P) {
    pending_operation_fill (P, type, oldpath, name, S);
  } else {
    if (release_mark) {
      dyn_release (release_mark);
    }
    pending_operation_push (pending_operation_create (type, oldpath, name, S));
  }
}