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
struct pending_operation {struct pending_operation* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  dyn_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pending_operation_apply (struct pending_operation*) ; 
 int /*<<< orphan*/  pending_operations_clear () ; 
 int /*<<< orphan*/  po_mrk ; 
 scalar_t__ po_use_mark ; 
 struct pending_operation* pol_head ; 
 int /*<<< orphan*/ * pol_tail ; 

void pending_operations_apply (void) {
  struct pending_operation *P;
  for (P = pol_head; P != NULL; P = P->next) {
    pending_operation_apply (P);
  }
  if (po_use_mark) {
    dyn_release (po_mrk);
  } else {
    pending_operations_clear ();
  }
  pol_head = pol_tail = NULL;
}