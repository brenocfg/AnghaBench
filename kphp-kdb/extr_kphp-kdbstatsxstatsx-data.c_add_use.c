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
 size_t counters_prime ; 

__attribute__((used)) static void add_use (struct counter *C) {
  C->next_use = Counters[counters_prime]->next_use;
  Counters[counters_prime]->next_use = C;
  C->prev_use = Counters[counters_prime];
  C->next_use->prev_use = C;
}