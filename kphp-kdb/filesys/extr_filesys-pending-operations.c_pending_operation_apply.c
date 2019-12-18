#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  st_mode; } ;
struct pending_operation {char* oldpath; char* newpath; int type; TYPE_1__ st; } ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  PO_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  delete_file (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  kprintf (char*) ; 
 int /*<<< orphan*/  lcopy_attrs (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  mkdir (char*,int /*<<< orphan*/ ) ; 
 char* po_newdir ; 
 char* po_olddir ; 
#define  pot_copy_attrs 133 
#define  pot_mkdir 132 
#define  pot_null 131 
#define  pot_remove 130 
#define  pot_rename 129 
#define  pot_symlink 128 
 int /*<<< orphan*/  rename (char*,char*) ; 
 int snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  symlink (char*,char*) ; 

void pending_operation_apply (struct pending_operation *P) {
  char full_oldpath[PATH_MAX], full_newpath[PATH_MAX];
  full_oldpath[0] = full_newpath[0] = 0;
  if (P->oldpath) {
    assert (snprintf (full_oldpath, PATH_MAX, "%s/%s", po_olddir, P->oldpath) < PATH_MAX);
  }
  if (P->newpath) {
    assert (snprintf (full_newpath, PATH_MAX, "%s/%s", po_newdir, P->newpath) < PATH_MAX);
  }
  switch (P->type) {
    case pot_null:
      kprintf ("pending_operation_apply (P.type == pot_null)\n");
      exit (1);
      break;
    case pot_mkdir:
      PO_ASSERT (mkdir (full_newpath, P->st.st_mode));
      PO_ASSERT (lcopy_attrs (full_newpath, &P->st));
      break;
    case pot_symlink:
      PO_ASSERT (symlink (P->oldpath, full_newpath));
      PO_ASSERT (lcopy_attrs (full_newpath, &P->st));
      break;
    case pot_rename:
      PO_ASSERT (rename (full_oldpath, full_newpath));
      PO_ASSERT (lcopy_attrs (full_newpath, &P->st));
      break;
    case pot_remove:
      PO_ASSERT (delete_file (full_newpath));
      break;
    case pot_copy_attrs:
      PO_ASSERT (lcopy_attrs (full_newpath, &P->st));
      break;
  }
}