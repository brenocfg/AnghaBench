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
struct counter {struct counter* prev_use; struct counter* next_use; } ;

/* Variables and functions */
 struct counter** Counters ; 
 int am_choose_hash_prime (double) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ counters_commit_head ; 
 int counters_prime ; 
 double max_counters ; 
 int /*<<< orphan*/  replay_logevent ; 
 int /*<<< orphan*/  reverse_index_mode ; 
 int /*<<< orphan*/  stats_replay_logevent ; 
 int /*<<< orphan*/  stats_replay_logevent_reverse ; 
 int /*<<< orphan*/  vkprintf (int,char*,double,int) ; 
 void* zzmalloc0 (int) ; 

int init_stats_data (int schema) {
  static int initialized = 0;
  if (initialized) {
    return 0;
  }
  initialized = 1;

  if (!reverse_index_mode) {
    replay_logevent = stats_replay_logevent;
  } else {
    replay_logevent = stats_replay_logevent_reverse;
  }

  counters_commit_head = 0;
  counters_prime = am_choose_hash_prime (max_counters * 1.5);
  vkprintf (1, "max_counters: %d, counters_prime: %d\n", max_counters, counters_prime);
  Counters = zzmalloc0 ((counters_prime + 1) * sizeof (struct counter *));
  struct counter *C;
  Counters[counters_prime] = C = zzmalloc0 (sizeof (struct counter));
  assert (C != NULL);
  C->next_use = C;
  C->prev_use = C;

  return 0;
}