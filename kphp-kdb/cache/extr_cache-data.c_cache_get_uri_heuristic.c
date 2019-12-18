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
struct cache_uri {int /*<<< orphan*/ * data; } ;
struct amortization_counter {double value; } ;

/* Variables and functions */
 size_t acounter_off ; 
 int amortization_counter_types ; 

double cache_get_uri_heuristic (const struct cache_uri *U) {
  int i;
  struct amortization_counter *C = (struct amortization_counter *) &U->data[acounter_off];
  double res = C->value;
  C++;
  for (i = 1; i < amortization_counter_types; i++) {
    if (res < C->value) {
      res = C->value;
    }
    C++;
  }
  return res;
}