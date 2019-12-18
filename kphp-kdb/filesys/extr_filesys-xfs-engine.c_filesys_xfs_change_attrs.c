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
struct stat {int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_atime; int /*<<< orphan*/  st_mode; } ;
struct lev_filesys_xfs_change_attrs {int filename_size; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  modtime; int /*<<< orphan*/  actime; int /*<<< orphan*/  mode; int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pending_operation_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,struct stat*) ; 
 int /*<<< orphan*/  pending_operation_push (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pot_copy_attrs ; 
 int /*<<< orphan*/  vkprintf (int,char*,char*) ; 

__attribute__((used)) static void filesys_xfs_change_attrs (struct lev_filesys_xfs_change_attrs *E) {
  char name[PATH_MAX];
  assert (E->filename_size < PATH_MAX - 1);
  memcpy (name, E->filename, E->filename_size);
  name[E->filename_size] = 0;
  vkprintf (3, "name = %s\n", name);
  struct stat st;
  st.st_mode = E->mode;
  st.st_atime = E->actime;
  st.st_mtime = E->modtime;
  st.st_uid = E->uid;
  st.st_gid = E->gid;
  pending_operation_push (pending_operation_create (pot_copy_attrs, NULL, name, &st));
}