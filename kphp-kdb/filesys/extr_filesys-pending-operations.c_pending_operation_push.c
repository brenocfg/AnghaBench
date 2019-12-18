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
 struct pending_operation* pol_head ; 
 struct pending_operation* pol_tail ; 

void pending_operation_push (struct pending_operation *P) {
  P->next = NULL;
  if (pol_head) {
    pol_tail->next = P;
    pol_tail = P;
  } else {
    pol_head = pol_tail = P;
  }
}