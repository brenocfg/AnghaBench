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
struct postponed_operation {scalar_t__ size; struct postponed_operation* next; } ;
struct TYPE_2__ {int tot_lists; } ;

/* Variables and functions */
 TYPE_1__ Header ; 
 int /*<<< orphan*/  assert (int) ; 
 struct postponed_operation** postponed ; 
 scalar_t__ postponed_replay ; 
 int /*<<< orphan*/  zfree (struct postponed_operation*,scalar_t__) ; 

void clear_postponed (int x) {
  assert (0 <= x && x < Header.tot_lists);
  if (postponed_replay) {
    return;
  }
  struct postponed_operation *E = postponed[x];
  if (E) {
    struct postponed_operation *G = E, *F;
    do {
      F = E;
      E = E->next;
      zfree (F, F->size + sizeof (struct postponed_operation));
    } while (G != E && F != E);
  }
  postponed[x] = 0;
}