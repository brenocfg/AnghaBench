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
struct counter {struct counter* prev; int /*<<< orphan*/  counter_id; struct counter* prev_use; int /*<<< orphan*/  next_use; } ;

/* Variables and functions */
 struct counter** Counters ; 
 int /*<<< orphan*/  assert (int) ; 
 size_t counters_prime ; 
 int /*<<< orphan*/  deleted_by_lru ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free_counter (struct counter*,int) ; 
 struct counter* get_counter_f (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int free_LRU () {
  if (verbosity >= 3) { fprintf (stderr, "free_LRU\n"); }
  if (Counters[counters_prime] == 0) {
    return 0;
  }
  if (verbosity >= 3) { fprintf (stderr, "first and last are %p and %p\n", Counters[counters_prime]->prev_use, Counters[counters_prime]->next_use); }
  
  if (Counters[counters_prime]->prev_use == Counters[counters_prime]) {
    if (verbosity >= 3) {
      fprintf (stderr, "No elements can be deleted by LRU. Failed to free mem.\n");
    }
    return 0;
  } else {
    struct counter *C = Counters[counters_prime]->prev_use;
    if (C) {
      struct counter *D = get_counter_f (C->counter_id, 0);
      while (D && D->prev != C) {
        D = D->prev;
      }
      if (D) {
        assert (D->prev == C);
        D->prev = 0;
      }
      free_counter (C, 1);
      deleted_by_lru++;
    }
    return 1;
  }
}