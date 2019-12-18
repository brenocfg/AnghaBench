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
struct time_amortization_table {int dummy; } ;
struct cache_uri {int /*<<< orphan*/ * data; } ;
struct amortization_counter {scalar_t__ value; } ;

/* Variables and functions */
 int CACHE_STAT_MAX_ACOUNTERS ; 
 int CORRECLATION_STATS_BUCKETS ; 
 struct time_amortization_table* TAT ; 
 size_t acounter_off ; 
 int /*<<< orphan*/  amortization_counter_increment (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  amortization_counter_precise_increment (struct time_amortization_table*,scalar_t__,int) ; 
 int amortization_counter_types ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cache_uri_bucket_reuse (struct cache_uri*) ; 
 int**** correlaction_stats ; 
 scalar_t__ cum_access_counters ; 

void cache_incr (struct cache_uri *U, int t) {
  #ifdef CACHE_FEATURE_CORRELATION_STATS
  int id[CACHE_STAT_MAX_ACOUNTERS];
  #endif
  int i;
  struct amortization_counter *C = (struct amortization_counter *) &U->data[acounter_off];
  struct time_amortization_table *T = TAT;
  for (i = 0; i < amortization_counter_types; i++) {
#ifdef CACHE_FEATURE_CORRELATION_STATS
    id[i] = (int) C->value;
    if (id[i] >= CORRECLATION_STATS_BUCKETS) {
      id[i] = CORRECLATION_STATS_BUCKETS - 1;
    }
    assert (id[i] >= 0);
#endif
    amortization_counter_precise_increment (T, cum_access_counters + i, t);
    amortization_counter_increment (T++, C++, t);
  }
  cache_uri_bucket_reuse (U);

#ifdef CACHE_FEATURE_CORRELATION_STATS
  int j;
  for (j = 1; j < amortization_counter_types; j++) {
    for (i = 0; i < j; i++) {
      correlaction_stats[i][j][id[i]][id[j]] += t;
    }
  }
#endif
}