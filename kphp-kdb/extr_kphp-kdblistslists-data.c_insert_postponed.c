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
struct postponed_operation {int size; struct postponed_operation* next; struct postponed_operation* prev; int /*<<< orphan*/  E; int /*<<< orphan*/  time; } ;
struct lev_generic {int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int tot_lists; } ;

/* Variables and functions */
 TYPE_1__ Header ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct lev_generic*,int) ; 
 int /*<<< orphan*/  now ; 
 struct postponed_operation** postponed ; 
 int postponed_operations_size ; 
 int /*<<< orphan*/  postponed_operations_total ; 
 scalar_t__ postponed_replay ; 
 int /*<<< orphan*/  vkprintf (int,char*,int,int /*<<< orphan*/ ,int) ; 
 struct postponed_operation* zmalloc (int) ; 

void insert_postponed (int x, struct lev_generic *E, int size) {
  assert (0 <= x && x < Header.tot_lists);
  if (postponed_replay) {
    return;
  }
  vkprintf (4, "Insert postponed: metafile_number = %d, lev_type = %d, size = %d\n", x, E->type, size);
  postponed_operations_total ++;
  struct postponed_operation *F = zmalloc (size + sizeof (struct postponed_operation));
  postponed_operations_size += size + sizeof (struct postponed_operation);
  F->size = size;
  F->next = 0;
  F->prev = 0;
  F->time = now;
  memcpy (F->E, E, size);
  if (!postponed[x]) {
    postponed[x] = F;
    F->next = F;
    F->prev = F;
  } else {
    struct postponed_operation *G = postponed[x];
    F->prev = G->prev;
    F->next = G;
    G->prev = F;
    F->prev->next = F;
  }
}