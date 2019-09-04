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
struct pending_operation {struct pending_operation* newpath; struct pending_operation* oldpath; struct pending_operation* next; } ;

/* Variables and functions */
 struct pending_operation* pol_head ; 
 int /*<<< orphan*/ * pol_tail ; 
 int strlen (struct pending_operation*) ; 
 int /*<<< orphan*/  zfree (struct pending_operation*,int) ; 

__attribute__((used)) static void pending_operations_clear (void) {
  struct pending_operation *P = pol_head, *W;
  for (P = pol_head; P != NULL; P = W) {
    W = P->next;
    if (P->oldpath) { zfree (P->oldpath, strlen (P->oldpath) + 1); }
    if (P->newpath) { zfree (P->newpath, strlen (P->newpath) + 1); }
    zfree (P, sizeof (*P));
  }
  pol_head = pol_tail = NULL;
}