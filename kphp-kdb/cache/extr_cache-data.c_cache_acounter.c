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
struct amortization_counter_precise {double value; } ;
struct amortization_counter {double value; } ;

/* Variables and functions */
 int /*<<< orphan*/ * TAT ; 
 size_t acounter_off ; 
 int /*<<< orphan*/  amortization_counter_precise_increment (int /*<<< orphan*/ *,struct amortization_counter_precise*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amortization_counter_update (int /*<<< orphan*/ *,struct amortization_counter*) ; 
 struct amortization_counter_precise* cum_access_counters ; 
 int get_acounter_id_by_t (int) ; 
 struct cache_uri* get_uri_f (char const* const,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const* const,char*) ; 

int cache_acounter (const char *const uri, int T, double *value) {
  const int id = get_acounter_id_by_t (T);
  if (id < 0) {
    return -1;
  }
  struct cache_uri *U = get_uri_f (uri, 0);
  if (U == NULL) {
    if (strcmp (uri, "__CUMULATIVE__")) {
      return -2;
    }
    struct amortization_counter_precise *C = cum_access_counters;
    C += id;
    amortization_counter_precise_increment (&TAT[id], C, 0);
    *value = C->value;
    return 0;
  } else {
    struct amortization_counter *C = (struct amortization_counter *) &U->data[acounter_off];
    C += id;
    amortization_counter_update (&TAT[id], C);
    *value = C->value;
    return 0;
  }
}