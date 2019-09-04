#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next_used; struct TYPE_6__* prev_used; } ;
typedef  TYPE_1__ user ;

/* Variables and functions */
 TYPE_1__* LRU_head ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_lru (char*,int) ; 
 int ltbl_get_rev (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  user_loaded (TYPE_1__*) ; 
 int /*<<< orphan*/  user_table ; 
 TYPE_1__* users ; 
 int verbosity ; 

void add_user_used (user *u) {
  if (verbosity > 3) {
    char tmp[100];
    sprintf (tmp, "?(+%d)", ltbl_get_rev (&user_table, (int)(u - users)));
    dump_lru (tmp, ltbl_get_rev (&user_table, (int)(u - users)));
  }

  assert (u != NULL);
  assert (user_loaded (u));

  assert (u->prev_used == NULL);
  assert (u->next_used == NULL);

  user *y = LRU_head->prev_used;

  u->next_used = LRU_head;
  LRU_head->prev_used = u;

  u->prev_used = y;
  y->next_used = u;
  if (verbosity > 3) {
    dump_lru ("!", 0);
  }
}