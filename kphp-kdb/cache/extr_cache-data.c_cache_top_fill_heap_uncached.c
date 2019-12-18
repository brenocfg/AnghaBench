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
struct cache_uri {int /*<<< orphan*/ * data; } ;
struct amortization_counter {int value; } ;
struct TYPE_2__ {int max_size; int size; struct cache_uri** H; } ;

/* Variables and functions */
 int CACHE_FEATURE_LONG_QUERIES ; 
 int CACHE_URI_BUCKETS ; 
 int GET_HEAP_VALUE (int) ; 
 struct cache_uri* PNEXT (struct cache_uri*) ; 
 scalar_t__ acounter_uncached_bucket_id ; 
 int /*<<< orphan*/  assert (int) ; 
 int cache_features_mask ; 
 int /*<<< orphan*/  cache_top_heap_insert_uri_optimized2 (struct cache_uri*) ; 
 scalar_t__ heap_acounter_id ; 
 size_t heap_acounter_off ; 
 TYPE_1__* heap_foreach ; 
 struct cache_uri* list_uncached ; 
 int /*<<< orphan*/  sizeof_uri (char*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int) ; 
 struct cache_uri* zmalloc0 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cache_top_fill_heap_uncached (int min_rate) {
  static struct cache_uri *fake = NULL;
  int i;
  assert (cache_features_mask & CACHE_FEATURE_LONG_QUERIES);
  if (fake == NULL) {
    fake = zmalloc0 (sizeof_uri (""));
  }
  struct amortization_counter *C = ((struct amortization_counter *) &fake->data[heap_acounter_off]);

  if (min_rate >= 1000000) {
    C->value = min_rate * 1e-6; // - 0
    min_rate = min_rate / 1000000 - 0;
  } else {
    C->value = min_rate ? min_rate : -1.0;
  }

  if (min_rate >= CACHE_URI_BUCKETS) {
    min_rate = CACHE_URI_BUCKETS - 1;
  }

  for (i = 1; i <= heap_foreach->max_size; i++) {
    heap_foreach->H[i] = fake;
  }
  heap_foreach->size = heap_foreach->max_size;
  struct cache_uri *U, *B;
  for (i = CACHE_URI_BUCKETS - 1; i >= min_rate; i--) {
    B = &list_uncached[i];
    for (U = PNEXT(B); U != B; U = PNEXT(U)) {
      cache_top_heap_insert_uri_optimized2 (U);
    }
    if (heap_acounter_id <= acounter_uncached_bucket_id && GET_HEAP_VALUE(1) > i) {
      vkprintf (2, "Skipping uncached buckets from %d to 0.\n", i - 1);
      break;
    }
  }
}