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
struct fwd_entry {scalar_t__ flags; struct db_table* table_ref; struct fwd_entry* fwd_next; } ;
struct db_table {int height; struct fwd_entry* fwd_first; } ;

/* Variables and functions */
 scalar_t__ FE_TABLEREF ; 
 int MAX_HEIGHT ; 

int dfs_check (struct db_table *A) {
  if (A->height != 1000) {
    return A->height;
  }
  A->height++;
  struct fwd_entry *FE;
  int mx = 0;
  for (FE = A->fwd_first; FE; FE = FE->fwd_next) {
    if (FE->flags == FE_TABLEREF) {
      int t = dfs_check (FE->table_ref);
      if (t > mx) {
	mx = t;
      }
      if (t > MAX_HEIGHT) {
	break;
      }
    }
  }
  if (mx != 999) {
    mx++;
  }
  return A->height = mx;
}