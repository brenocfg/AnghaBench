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
struct stat {int dummy; } ;
struct pending_operation {int type; int /*<<< orphan*/  st; void* newpath; void* oldpath; } ;
typedef  enum pending_operation_tp { ____Placeholder_pending_operation_tp } pending_operation_tp ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct stat*,int) ; 
 struct pending_operation* zmalloc0 (int) ; 
 void* zstrdup (char const* const) ; 

struct pending_operation *pending_operation_create (enum pending_operation_tp type, const char *const oldpath, const char *const newpath, struct stat *st) {
  struct pending_operation *P = zmalloc0 (sizeof (struct pending_operation));
  P->type = type;
  if (oldpath) {
    P->oldpath = zstrdup (oldpath);
  }
  if (newpath) {
    P->newpath = zstrdup (newpath);
  }
  if (st) {
    memcpy (&P->st, st, sizeof (struct stat));
  }
  return P;
}