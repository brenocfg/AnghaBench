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

/* Variables and functions */
 int COUNTERS_PRIME ; 
 int* Counters ; 
 int* T ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stdout ; 

void counter_add (int counter_id) {
  int h1, h2;
  int D;
  if (!counter_id) { return; }
  //if (counter_id < 0) { return; } //DEBUG
  h1 = h2 = counter_id;
  if (h1 < 0) { h1 = 17-h1; }
  h1 = h1 % COUNTERS_PRIME;
  if (h2 < 0) { h2 = 17239-h2; }
  if (h1 < 0 || h2 < 0) { return; }
  h2 = 1 + (h2 % (COUNTERS_PRIME - 1));
  while ((D = Counters[h1]) != 0) {
    if (D == counter_id) { 
      T[h1]++;
      return; 
    }
    h1 += h2;
    if (h1 >= COUNTERS_PRIME) { h1 -= COUNTERS_PRIME; }
  }
  Counters[h1] = counter_id;
  T[h1] = 1;
  fprintf (stdout, "%d\n", counter_id);
  return;
}